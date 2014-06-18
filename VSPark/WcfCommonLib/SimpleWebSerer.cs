using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Threading;
using System.IO;
using System.Configuration;

namespace WcfCommonLib
{
    public class SimpleWebSerer
    {
        public class WebEVentArgs : EventArgs
        {
            private string postString;

            public string QueryString
            {
                get { return this.postString; }
                set { this.postString = value; }
            }   
        }

        public delegate void QueryEventHandler(object sender, WebEVentArgs e);
        public event QueryEventHandler QueryEvent;

        protected void OnQueryEvent( WebEVentArgs e )
        {
            if (null == QueryEvent)
            {
                return;
            }

            QueryEvent(this, e );
        }

        private HttpListener webListener = null;
        private IAsyncResult webRequest = null;
        //private Thread WebThread = null;
        private AsyncCallback webAsyncCallback = null;

        private string strPrefix = null;

        public SimpleWebSerer()
        {
            // URI http://www.contoso.com/whatsnew.aspx?date=today
            //"http://127.0.0.1:9010/"
            strPrefix = ConfigurationManager.AppSettings.Get("WebServerPrefix");
        }

        private void ListenerCallback(IAsyncResult iResult)
        {
            HttpListener listener = (HttpListener)iResult.AsyncState;
            if (!listener.IsListening)
            {
                return;
            }

            // Call EndGetContext to complete the asynchronous operation.

            HttpListenerContext context = listener.EndGetContext(iResult);
            HttpListenerRequest request = context.Request;

            if (request.HttpMethod.ToUpper() == "POST" && request.HasEntityBody)
            {
                Stream body = request.InputStream;
                Encoding coding = request.ContentEncoding;
                StreamReader reader = new StreamReader(body, coding);
                string strBody = reader.ReadToEnd();

                body.Close();
                reader.Close();

                //System.Diagnostics.Debug.Print( "Server" );
                //System.Diagnostics.Debug.Print(strBody);

                WebEVentArgs e = new WebEVentArgs();
                e.QueryString = strBody;
                OnQueryEvent(e);
            }
            // Obtain a response object.

            HttpListenerResponse response = context.Response;
            response.Close();

            // Construct a response.
#if false
            string responseString = "<HTML><BODY> Hello world!</BODY></HTML>";
            byte[] buffer = Encoding.UTF8.GetBytes(responseString);
            // Get a response stream and write the response to it.

            response.ContentLength64 = buffer.Length;
            System.IO.Stream output = response.OutputStream;
            output.Write(buffer, 0, buffer.Length);
            // You must close the output stream.

            output.Close();
#endif
            if (listener.IsListening)
            {
                listener.BeginGetContext(webAsyncCallback, listener);
            }
        }

        public void StartServer()
        {
            if (!HttpListener.IsSupported)
            {
                return;
            }

            if (null == webAsyncCallback)
            {
                webAsyncCallback = new AsyncCallback(ListenerCallback);
            }

            if (null == webListener)
            {
                webListener = new HttpListener();
            }

            if (!webListener.Prefixes.Contains(strPrefix ))
            {
                webListener.Prefixes.Add(strPrefix );
            }

            if (!webListener.IsListening)
            {
                webListener.Start();
            }

            webRequest = webListener.BeginGetContext( webAsyncCallback, webListener );
        }

        public void StopServer()
        {
            if (null == webListener)
            {
                return;
            }

            if (!webListener.IsListening)
            {
                return;
            }

            webListener.Stop();
            webListener.Close();
        }

    }
}
