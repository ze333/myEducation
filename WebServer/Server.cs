using System;
using System.Net.Sockets;
using System.Net;
using System.Threading;
using System.Text;
using System.Collections.Generic;
using System.IO;

namespace SimpleWebServer
{
    class Server
    {
        private bool _running; 

        private int timeout = 8; 
        private readonly Encoding _charEncoder = Encoding.UTF8; 
        private Socket _serverSocket; 
        private string _contentPath; 

        private readonly Dictionary<string, string> _extensions = new Dictionary<string, string>()
        { 
            //{ "extension", "content type" }
            { "htm", "text/html" },
            { "html", "text/html" },
            { "xml", "text/xml" },
            { "txt", "text/plain" },
            { "css", "text/css" },
            { "png", "image/png" },
            { "gif", "image/gif" },
            { "jpg", "image/jpg" },
            { "jpeg", "image/jpeg" }
        };

        public bool Start(IPAddress ipAddress, int port, int maxNOfCon, string contentPath)
        {
            if (_running) return false;

            try
            {
                _serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                _serverSocket.Bind(new IPEndPoint(ipAddress, port));
                _serverSocket.Listen(maxNOfCon);
                _serverSocket.ReceiveTimeout = timeout;
                _serverSocket.SendTimeout = timeout;
                _running = true;
                _contentPath = contentPath;
            }
            catch { return false; }

            Thread requestListenerT = new Thread(() =>
            {
                while (_running)
                {
                    Socket clientSocket;
                    try
                    {
                        clientSocket = _serverSocket.Accept();
                        Thread requestHandler = new Thread(() =>
                        {
                            clientSocket.ReceiveTimeout = timeout;
                            clientSocket.SendTimeout = timeout;
                            try { HandleTheRequest(clientSocket); }
                            catch
                            {
                                try { clientSocket.Close(); }
                                catch{}
                            }
                        });
                        requestHandler.Start();
                    }
                    catch{}
                }
            });
            requestListenerT.Start();

            return true;
        }

        public void Stop()
        {
            if (_running)
            {
                _running = false;
                try { _serverSocket.Close(); }
                catch { }
                _serverSocket = null;
            }
        }

        private void HandleTheRequest(Socket clientSocket)
        {
            byte[] buffer = new byte[10240]; 
            int receivedBCount = clientSocket.Receive(buffer); 
            string strReceived = _charEncoder.GetString(buffer, 0, receivedBCount);

            // Парсим запрос
            string httpMethod = strReceived.Substring(0, strReceived.IndexOf(" ", StringComparison.Ordinal));

            int start = strReceived.IndexOf(httpMethod, StringComparison.Ordinal) + httpMethod.Length + 1;
            int length = strReceived.LastIndexOf("HTTP", StringComparison.Ordinal) - start - 1;
            string requestedUrl = strReceived.Substring(start, length);

            string requestedFile;
            if (httpMethod.Equals("GET") || httpMethod.Equals("POST"))
                requestedFile = requestedUrl.Split('?')[0];
            else 
            {
                NotImplemented(clientSocket);
                return;
            }

            requestedFile = requestedFile.Replace("/", "\\").Replace("\\..", ""); 
            start = requestedFile.LastIndexOf('.') + 1;
            if (start > 0)
            {
                length = requestedFile.Length - start;
                string extension = requestedFile.Substring(start, length);
                if (_extensions.ContainsKey(extension))
                    if (File.Exists(_contentPath + requestedFile)) 
                       SendOkResponse(clientSocket, File.ReadAllBytes(_contentPath + requestedFile), _extensions[extension]);
                    else
                        NotFound(clientSocket); 
            }
            else
            {

                if (requestedFile.Substring(length - 1, 1) != "\\")
                    requestedFile += "\\";
                if (File.Exists(_contentPath + requestedFile + "index.htm"))
                    SendOkResponse(clientSocket, File.ReadAllBytes(_contentPath + requestedFile + "\\index.htm"), "text/html");
                else if (File.Exists(_contentPath + requestedFile + "index.html"))
                    SendOkResponse(clientSocket, File.ReadAllBytes(_contentPath + requestedFile + "\\index.html"), "text/html");
                else
                    NotFound(clientSocket);
            }
        }

        private void NotImplemented(Socket clientSocket)
        {
            SendResponse(clientSocket, "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head><body><h2>Atasoy Simple Web Server</h2><div>501 - Method Not Implemented</div></body></html>", "501 Not Implemented", "text/html");
        }

        private void NotFound(Socket clientSocket)
        {
            SendResponse(clientSocket, "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head><body><h2>Atasoy Simple Web Server</h2><div>404 - Not Found</div></body></html>", "404 Not Found", "text/html");
        }

        private void SendOkResponse(Socket clientSocket, byte[] bContent, string contentType)
        {
            SendResponse(clientSocket, bContent, "200 OK", contentType);
        }

        // Для строк
        private void SendResponse(Socket clientSocket, string strContent, string responseCode, string contentType)
        {
            byte[] bContent = _charEncoder.GetBytes(strContent);
            SendResponse(clientSocket, bContent, responseCode, contentType);
        }

        // Для массива байтов
        private void SendResponse(Socket clientSocket, byte[] bContent, string responseCode, string contentType)
        {
            try
            {
                byte[] bHeader = _charEncoder.GetBytes(
                                    "HTTP/1.1 " + responseCode + "\r\n"
                                  + "Server: Наш простой ВЭБсервер\r\n"
                                  + "Content-Length: " + bContent.Length.ToString() + "\r\n"
                                  + "Connection: close\r\n"
                                  + "Content-Type: " + contentType + "\r\n\r\n");
                clientSocket.Send(bHeader);
                clientSocket.Send(bContent);
                clientSocket.Close();
            }
            catch { }
        }
    }
}
