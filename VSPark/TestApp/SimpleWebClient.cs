using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Configuration;

namespace TestApp
{
    class SimpleWebClient
    {
        private WebClient client = null;

        public SimpleWebClient()
        {
            client = new WebClient();
            client.BaseAddress = "http://127.0.0.1:9011/";
            //client.BaseAddress = ConfigurationManager.AppSettings.Get("WebServerPrefix");
        }

        public void PostString(string strWhere)
        {
            string strResponse = client.UploadString("", strWhere);
            System.Diagnostics.Debug.Print( strResponse );
        }
    }
}
