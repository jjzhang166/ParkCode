using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Configuration;
using System.Collections;

namespace WcfCommonLib
{
    public class TcpServer
    {
        private Int32 nParkIDSize = 10;
        private Socket listener = null;
        private Hashtable peerSocks = null;
        private Int32 nPort = 9012;
        private IPEndPoint endPoint = null;
        private AsyncCallback asyncAccept = null;
        private AsyncCallback asyncSend= null;
        private AsyncCallback asyncReceive = null;

        private class SendState
        {
            public Socket peerSocket = null;
            public string strParkID = null;
        }

        public class MessageEventArgs : EventArgs
        {
            public MessageEventArgs(string strMessage, bool bCrossThread)
            {
                this.strMessage = strMessage;
                this.bCrossThread = bCrossThread;
            }

            public string strMessage;
            public bool bCrossThread;
        }

        protected void OnMessageEvent(MessageEventArgs e)
        {
            if (null == MessageEvent)
            {
                return;
            }

            MessageEvent(this, e);
        }

        public delegate void MessageEventHandler(object sender, MessageEventArgs e);
        public event MessageEventHandler MessageEvent;

        private void SendMessage(Socket peerSocket, string strParkID, bool bCrossThread, string strExtra)
        {
            StringBuilder builder = new StringBuilder();

            IPEndPoint clientIP = peerSocket.RemoteEndPoint as IPEndPoint;
            IPEndPoint peerIP = peerSocket.LocalEndPoint as IPEndPoint;

            builder.AppendFormat("【ParkID:{0}】【Client {1}:{2}】【Peer {3}:{4}】{5}", strParkID,
                clientIP.Address.ToString(), clientIP.Port,
                peerIP.Address.ToString(), peerIP.Port,
                strExtra );

            OnMessageEvent(new MessageEventArgs(builder.ToString(), bCrossThread));
        }

        private class ReceiveStateObject
        {
            public Socket workSocket = null;
            public const int BufferSize = 9;//Heartbeat
            public byte[] buffer = new byte[BufferSize];
            public string strParkID;
        }

        private void ReadCallback(IAsyncResult ar)
        {
            ReceiveStateObject state = (ReceiveStateObject)ar.AsyncState;
            Socket handler = state.workSocket;

            try
            {
                int bytesRead = handler.EndReceive(ar);

                if (0 < bytesRead)
                {
                    string strPing = Encoding.UTF8.GetString(state.buffer);
                    SendMessage(handler, state.strParkID, true, strPing);
                    //OnMessageEvent(new MessageEventArgs(strPing, true));
                }

                if (handler.Connected)
                {
                    handler.BeginReceive(state.buffer, 0, ReceiveStateObject.BufferSize, 0, asyncReceive, state);
                }
            }
            catch (Exception e)
            {
                OnMessageEvent( new MessageEventArgs( CommonFunction.GetExceptionMessage(e).ToString(), true));
            }
        }

        private void AsyncAcceptCB(IAsyncResult iResult)
        {
            try
            {
                Socket objListener = (Socket)iResult.AsyncState;

                byte[] parkIDBuffer;
                Int32 nTransferSize = 0;
                Socket peerSocket = objListener.EndAccept(out parkIDBuffer, out nTransferSize, iResult);
                string strExtra = "Connected";

                string strParkID = Encoding.UTF8.GetString(parkIDBuffer, 0, nTransferSize);
                StringBuilder builder = new StringBuilder();
                builder.AppendFormat("Accept to receive data【{0} Size = {1}】", strParkID, nTransferSize);
                OnMessageEvent(new MessageEventArgs(builder.ToString(), true));

                if (nParkIDSize <= nTransferSize)
                {
                    strParkID = Encoding.UTF8.GetString(parkIDBuffer, 0, nParkIDSize);

                    lock (this)

                        if (peerSocks.ContainsKey(strParkID))
                        {
                            Socket peer = GetPeerSocket(strParkID);
                            if (null != peer)
                            {
                                peer.Close();
                            }

                            peerSocks.Remove(strParkID);
                            strExtra += "【Remove existence】";
                        }

                    peerSocket.ReceiveTimeout = 1000;
                    peerSocket.SendTimeout = 2000;
                    peerSocks.Add(strParkID, peerSocket);

                    ReceiveStateObject state = new ReceiveStateObject();
                    state.workSocket = peerSocket;
                    state.strParkID = strParkID;
                    peerSocket.BeginReceive(state.buffer, 0, ReceiveStateObject.BufferSize, 0, asyncReceive, state);

                    SendMessage(peerSocket, strParkID, true, strExtra);
                }

                if (objListener.IsBound)
                {
                    objListener.BeginAccept(nParkIDSize, asyncAccept, objListener);
                }
            }
            catch (Exception e)
            {
                OnMessageEvent(new MessageEventArgs(CommonFunction.GetExceptionMessage(e).ToString(), true));
            }
        }

        public TcpServer()
        {
            string strPort = ConfigurationManager.AppSettings.Get("ListenerPort");
            nPort = Convert.ToInt32(strPort);
            endPoint = new IPEndPoint(IPAddress.Any, nPort);
            peerSocks = new Hashtable();
            asyncSend = new AsyncCallback(SendCB);
            asyncReceive = new AsyncCallback(ReadCallback);
        }

        private Socket GetPeerSocket(string strParkID)
        {
            Socket peer = peerSocks[strParkID] as Socket;
            return peer;
        }

        public void Send2Client(string strParkID, string strData)
        {
            Socket peer = null;
            lock(this)

            peer = GetPeerSocket(strParkID);
            if (null == peer || !peer.Connected )
            {
                if (null != peer)
                {
                    //peer.Close();
                    //peerSocks.Remove(strParkID);
                    OnMessageEvent(new MessageEventArgs("Send2Client Peer Disconnected", true));
                }

                OnMessageEvent(new MessageEventArgs(null == peer ? "Send2Client null == peer" : "Send2Client false == Connected", true));
                return;
            }
#if false
            try
            {
                peer.Receive(byReceivePing);//DDoS
            }
            catch (Exception e)
            {
                OnMessageEvent(new MessageEventArgs(CommonFunction.GetExceptionMessage(e).ToString(), false));
            }
#endif
            strData += "\n";
            byte[] byBuffer = Encoding.UTF8.GetBytes(strData);
            SendState state = new SendState();
            state.peerSocket = peer;
            state.strParkID = strParkID;
            peer.BeginSend(byBuffer, 0, byBuffer.Length, SocketFlags.None, asyncSend, state);
        }

        private void SendCB(IAsyncResult ar)
        {
            try
            {
                SendState state = (SendState)ar.AsyncState;
                Int32 nRet = state.peerSocket.EndSend(ar);
                string strExtra = "Server send to client size : " + nRet.ToString();

                SendMessage(state.peerSocket, state.strParkID, true, strExtra);
            }
            catch (Exception e)
            {
                OnMessageEvent(new MessageEventArgs(CommonFunction.GetExceptionMessage(e).ToString( ), true));
            }
        }

        public void StartServer()
        {
            if (null == listener)
            {
                listener = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp );
            }

            if (listener.IsBound)
            {
                return;
            }

            if (null == asyncAccept)
            {
                asyncAccept = new AsyncCallback(AsyncAcceptCB);
            }

            listener.Bind(endPoint);
            listener.Listen(1000);

            listener.BeginAccept(nParkIDSize, asyncAccept, listener);
        }

        public void StopServer()
        {
            if (null == listener)
            {
                return;
            }

            //listener.Shutdown(SocketShutdown.Both);
            listener.Close();
        }
    }
}
