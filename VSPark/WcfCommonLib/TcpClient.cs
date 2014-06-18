using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Configuration;
using System.Collections;
using System.Threading;

namespace WcfCommonLib
{
    public class TcpClient
    {
        private class ReadStateObject
        {
            public Socket workSocket = null;
            public const int BUFFER_SIZE = 1024;
            public byte[] buffer = new byte[BUFFER_SIZE];
            public StringBuilder sb = new StringBuilder();
        }

        public class SocketEVentArgs : EventArgs
        {
            private string strQueryString;

            public string QueryString
            {
                get { return this.strQueryString; }
                set { this.strQueryString = value; }
            }
        }

        public delegate void QueryEventHandler(object sender, SocketEVentArgs e);
        public event QueryEventHandler QueryEvent;

        public delegate void MessageEventHandler(object sender, MessageEventArgs e);
        public event MessageEventHandler MessageEvent;

        protected void OnQueryEvent(SocketEVentArgs e)
        {
            if (null == QueryEvent)
            {
                return;
            }

            QueryEvent(this, e);
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

        private Socket client = null;
        private string strIP = null;
        private Int32 nPort = 0;
        private string strParkID = null;
        private IPEndPoint endPoint = null;
        private AsyncCallback asyncRead = null;
        private ReadStateObject readState = new ReadStateObject();
        private AsyncCallback asyncConnectCB = null;

        private void AsyncConnect(IAsyncResult ar)
        {
            lock (this) 

            try
            {
                Socket s = ar.AsyncState as Socket;
                s.EndConnect(ar);

                if (s.Connected)
                {
                    readState.workSocket = client;
                    strParkID = ConfigurationManager.AppSettings.Get("ParkID");
                    byte[] dataBuffer = Encoding.UTF8.GetBytes(strParkID);
                    s.Send(dataBuffer);

                    s.BeginReceive(readState.buffer, 0, ReadStateObject.BUFFER_SIZE, SocketFlags.None, ReadCB, readState);

                    IPEndPoint rIP = s.RemoteEndPoint as IPEndPoint;
                    IPEndPoint lIP = s.LocalEndPoint as IPEndPoint;
                    StringBuilder builder = new StringBuilder();
                    builder.AppendFormat("Connect【{0}:{1}】 to 【{2}:{3}】", lIP.Address.ToString(), lIP.Port, rIP.Address.ToString(), rIP.Port);
                    OnMessageEvent(new MessageEventArgs(builder.ToString(), true));
                }
            }
            catch (Exception e)
            {
                //System.Diagnostics.Debug.Print(e.Message);
                OnMessageEvent(new MessageEventArgs(e.Message, true));
            }
        }

        private void ReadCB(IAsyncResult ar)
        {
            ReadStateObject state = (ReadStateObject)ar.AsyncState;
            if (!state.workSocket.Connected)
            {
                return;
            }

            int nReadSize = 0;

            try
            {
                nReadSize = state.workSocket.EndReceive(ar);
            }
            catch (Exception ex)
            {
                //System.Diagnostics.Debug.Print(ex.Message);
                OnMessageEvent(new MessageEventArgs(ex.Message, true));
            }

            if (0 < nReadSize)
            {
                string strQuery = Encoding.UTF8.GetString(state.buffer, 0, nReadSize);

                SocketEVentArgs e = new SocketEVentArgs();
                e.QueryString = strQuery;
                OnQueryEvent(e);
            }

            if (state.workSocket.Connected)
            {
                state.workSocket.BeginReceive(state.buffer, 0, ReadStateObject.BUFFER_SIZE, SocketFlags.None, ReadCB, state);
            }
        }

        public TcpClient()
        {
            strIP = ConfigurationManager.AppSettings.Get("SocketServer");
            string strPort = ConfigurationManager.AppSettings.Get("SocketPort");
            nPort = Convert.ToInt32(strPort);
            IPAddress addr = IPAddress.Parse(strIP);
            endPoint = new IPEndPoint(addr, nPort);
            asyncRead = new AsyncCallback(ReadCB);
            asyncConnectCB = new AsyncCallback(AsyncConnect);
        }

        private void ConnectCB(IAsyncResult ar)
        {
            Socket socketClient = (Socket)ar.AsyncState;
            if (null == socketClient)
            {
                return;
            }
            socketClient.EndConnect(ar);

            if (socketClient.Connected)
            {
                strParkID = ConfigurationManager.AppSettings.Get("ParkID");
                byte[] dataBuffer = Encoding.UTF8.GetBytes(strParkID);
                socketClient.Send(dataBuffer);
            }
        }

        public void ReconnectServer()
        {
            //bool blockingState = client.Blocking;

            try
            {
                byte[] tmp = Encoding.UTF8.GetBytes("Heartbeat");//new byte[1];

                //client.Blocking = true;
                int nRet = client.Send(tmp, tmp.Length, SocketFlags.None);
                //SendMessage(client, false, "Ping Size = " + nRet.ToString( ) );
            }
            catch (SocketException e)
            {
                // 10035 == WSAEWOULDBLOCK
                if (e.NativeErrorCode.Equals(10035))
                    System.Diagnostics.Debug.Print("Still Connected, but the Send would block");
                else
                {
                    System.Diagnostics.Debug.Print("Disconnected: error code {0}!", e.NativeErrorCode);
                    //client.Blocking = blockingState;

                    ConnectServer(true);
                    SendMessage(client, false, "Reconnect");
                }

                OnMessageEvent(new MessageEventArgs(e.Message, false));
            }
        }

        private void SendMessage(Socket clientSocket, bool bCrossThread, string strExtra)
        {
            StringBuilder builder = new StringBuilder();

            IPEndPoint rIP = clientSocket.RemoteEndPoint as IPEndPoint;
            IPEndPoint lIP = clientSocket.LocalEndPoint as IPEndPoint;

            builder.AppendFormat("{0}【{1}:{2}】 to 【{3}:{4}】【{5}】", strExtra, lIP.Address.ToString(), lIP.Port, rIP.Address.ToString(), rIP.Port, client.Connected);

            OnMessageEvent(new MessageEventArgs(builder.ToString(), bCrossThread));
        }

        public void ConnectServer(bool bReconnected)
        {
            lock (this) 

            if (null != client)
            {
                client.Close();
                client = null;
            }

            client = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            client.Blocking = false;
            client.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.Linger, new LingerOption(false, 0));
            client.BeginConnect(endPoint, asyncConnectCB, client);
        }

        public void ConnectServer1( )
        {
            if (null != client)
            {
                client.Close();
                client = null;
            }

            client = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            //client.BeginConnect(endPoint, asyncConnect, client);
            client.Connect(endPoint);
            if (client.Connected)
            {
                readState.workSocket = client;
                strParkID = ConfigurationManager.AppSettings.Get("ParkID");
                byte[] dataBuffer = Encoding.UTF8.GetBytes(strParkID);
                client.Send(dataBuffer);

                client.BeginReceive(readState.buffer, 0, ReadStateObject.BUFFER_SIZE, SocketFlags.None, ReadCB, readState);
            }
        }

        public void DisconnectServer()
        {
            //client.Disconnect(true);
            client.Close();
        }
    }
}
