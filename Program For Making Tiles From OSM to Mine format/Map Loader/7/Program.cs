using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace MapDownloader7
{
    class Program
    {
        static void Main(string[] args)
        {
            ServicePointManager.SecurityProtocol = SecurityProtocolType.Ssl3 | SecurityProtocolType.Tls | SecurityProtocolType.Tls11 | SecurityProtocolType.Tls12;
            int i = 0;
            System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
            double[] longtitudes = new double[] { 39.909736, 44.087585, 47.989922, 51.618016, 54.977613, 58.077876, 60.930432, 63.548552, 65.946472, 68.138852, 70.140365, 71.965388, 73.627789, 75.140778, 76.516819, 77.767582, 78.903929, 79.935918, 80.872827, 81.723188, 82.494824, 83.194896, 83.829945, 84.405941, 84.928321 };
            double[] longtitudes11 = longtitudes.Reverse().ToArray();
            Console.WriteLine(longtitudes11.Count());
            int start = 20;
            int end = 22;
        M: for (int kk = start; kk < end; kk++)   
            {
                string currentToken = "052415";
                String long2 = "," + longtitudes11[kk] ;
                String long1 = "," + longtitudes11[kk + 1]+ ",";
                double deltaLat1 = 0.6263 * 16;
                double lat1 = 19.667199+0.6263 * 16;
                for (i = 1; i < 16; i++)
                {
                    try
                    {
                        using (WebClient client = new WebClient())
                        {
                            String currentUrl = "https://render.openstreetmap.org/cgi-bin/export?bbox=" + (lat1).ToString() + long1 + (lat1+deltaLat1).ToString() + long2 + "&scale=4000000&format=svg";
                            Console.WriteLine(currentUrl);
                            Uri url = new Uri(currentUrl);
                            client.Headers.Add(HttpRequestHeader.Authorization, "render.openstreetmap.org");
                            client.Headers.Add("method", "GET");
                            client.Headers.Add("path", "/cgi-bin/export?bbox=28.83746292791811,59.63284874301492,30.49090531073061,60.26414816040228&scale=250000&format=svg");
                            client.Headers.Add("scheme", "https");
                            client.Headers.Add(HttpRequestHeader.Accept, "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9");
                            //client.Headers.Add(HttpRequestHeader.AcceptEncoding, "gzip, deflate, br");
                            client.Headers.Add(HttpRequestHeader.AcceptLanguage, "ru-RU,ru;q=0.9,en-US;q=0.8,en;q=0.7");
                            client.Headers.Add(HttpRequestHeader.Cookie, "_osm_totp_token=" + currentToken);
                            client.Headers.Add("sec-ch-ua", "\"Chromium\";v=\"88\", \"Google Chrome\";v=\"88\", \"; Not A Brand\";v=\"99\"");
                            client.Headers.Add(HttpRequestHeader.Referer, "https://www.openstreetmap.org/");
                            client.Headers.Add("sec-fetch-dest", "document");
                            client.Headers.Add("sec-fetch-mode", "navigate");
                            client.Headers.Add("sec-fetch-site", "same-site");
                            client.Headers.Add("sec-fetch-user", "?1");
                            client.Headers.Add("upgrade-insecure-requests", "1");
                            client.Headers.Add(HttpRequestHeader.UserAgent, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.190 Safari/537.36");
                            client.QueryString.Add("bbox", "104.49886322021486,41.725461744125646,104.64717864990236,41.951064612666684");
                            client.QueryString.Add("scale", "250000");
                            client.QueryString.Add("format", "svg");
                            Console.WriteLine(i);
                            client.DownloadFile(url, i.ToString() + "_" + kk.ToString() + ".svg");

                        }

                    }
                    catch (Exception e)
                    {
                        Console.WriteLine(e);
                        i--;
                        lat1 -= deltaLat1;
                        System.Threading.Thread.Sleep(5000);
                        String currentUrl = "https://www.openstreetmap.org/#map=12/41.8368/104.5450&layers=N";
                        HttpWebRequest tQ = (HttpWebRequest)HttpWebRequest.Create(currentUrl);
                        tQ.Accept = "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9";
                        tQ.UserAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.41 YaBrowser/21.2.0.1097 Yowser/2.5 Safari/537.36";
                        tQ.ContentType = "text/html; charset=utf-8";
                        tQ.Referer = currentUrl;
                        HttpWebResponse tS;
                        try
                        {
                            tS = (HttpWebResponse)tQ.GetResponse();
                        }
                        catch (Exception eee)
                        {
                            start = start + 2;
                            Console.WriteLine(eee);
                            Console.WriteLine("goto");
                            goto M;
                        }
                        string tC = tS.Headers["Set-Cookie"];
                        var cc = tC.IndexOf("_osm_totp_token=");
                        currentToken = tC.Substring(cc + "_osm_totp_token=".Length, 6);
                        //string num = tC.Trim(, 2);
                        Console.WriteLine(tC);
                    }
                    lat1 += deltaLat1;
                    Console.WriteLine("i=" + i.ToString());
                }

            }


            int ggg = 0;
        }
    }
}
