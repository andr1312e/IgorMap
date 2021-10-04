using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace MapLoader9
{
    class Program
    {
        static void Main(string[] args)
        {
            int i = 0;
            System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
            double[] longtitudes11 = new double[] { 38.822591, 39.909736, 40.979898, 42.032975, 43.068888, 44.087585, 45.089036, 46.073231, 47.040182, 47.989922, 48.922499, 49.837983, 50.736455, 51.618016, 52.48278, 53.330873, 54.162434, 54.977613, 55.776573, 56.559482, 57.326521, 58.077876, 58.813742, 59.534318, 60.239811, 60.930432, 61.606397, 62.267923, 62.915233, 63.548552, 64.168107, 64.774125, 65.366837, 65.946472, 66.51326, 67.067433, 67.60922, 68.138852, 68.656555, 69.162558, 69.657086, 70.140365, 70.612614, 71.074057, 71.524909, 71.965388, 72.395706, 72.816073, 73.2267, 73.627789, 74.019543, 74.402163, 74.775843, 75.140778, 75.497157, 75.845168, 76.184995, 76.516819, 76.840817, 77.157163, 77.466029, 77.767582, 78.061989, 78.34941, 78.630006, 78.903929, 79.171334, 79.432371, 79.687184, 79.935918, 80.178713, 80.415708, 80.647035, 80.872827, 81.093214, 81.308321, 81.518272, 81.723188, 81.923187, 82.118384, 82.308893, 82.494824, 82.676285, 82.853382, 83.026219, 83.194896, 83.359512};
            Console.WriteLine(longtitudes11.Length);
            int start = 0;
            int end = 80;
            M: for (int kk = start; kk < end; kk++)
            {
                string currentToken = "438357";
                String long1 = "," + longtitudes11[kk] + ",";
                String long2 = "," + longtitudes11[kk + 1];
                //double lat1 = -178.490775;
                double lat1 = -180.00000;
                double deltaLat1 = 1.509225;
                for (i = 64; i < 65; i++)
                {

                    try
                    {
                        using (WebClient client = new WebClient())
                        {

                            String currentUrl = "https://render.openstreetmap.org/cgi-bin/export?bbox=" + lat1.ToString() + long1 + (lat1 + deltaLat1).ToString() + long2 + "&scale=2000000&format=svg";
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
                            lat1 += deltaLat1;

                        }
                    }
                    catch (Exception e)
                    {
                        Console.WriteLine(e);
                        System.Threading.Thread.Sleep(5000);
                        String currentUrl = "https://www.openstreetmap.org/#map=8/41.8368/104.5450&layers=N";
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
                        tS = (HttpWebResponse)tQ.GetResponse();
                        string tC = tS.Headers["Set-Cookie"];
                        var cc = tC.IndexOf("_osm_totp_token=");
                        currentToken = tC.Substring(cc + "_osm_totp_token=".Length, 6);
                        //string num = tC.Trim(, 2);
                        Console.WriteLine(tC);
                        i = i - 1;
                    }

                    Console.WriteLine("i=" + i.ToString());
                }

            }


            int ggg = 0;


            //int i = 0;
            //System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
            //double[] longtitudes11 = new double[] { 38.822591, 39.909736, 40.979898, 42.032975, 43.068888, 44.087585, 45.089036, 46.073231, 47.040182, 47.989922, 48.922499, 49.837983, 50.736455, 51.618016, 52.48278, 53.330873, 54.162434, 54.977613, 55.776573, 56.559482, 57.326521, 58.077876, 58.813742, 59.534318, 60.239811, 60.930432, 61.606397, 62.267923, 62.915233, 63.548552, 64.168107, 64.774125, 65.366837, 65.946472, 66.51326, 67.067433, 67.60922, 68.138852, 68.656555, 69.162558, 69.657086, 70.140365, 70.612614, 71.074057, 71.524909, 71.965388, 72.395706, 72.816073, 73.2267, 73.627789, 74.019543, 74.402163, 74.775843, 75.140778, 75.497157, 75.845168, 76.184995, 76.516819, 76.840817, 77.157163, 77.466029, 77.767582, 78.061989, 78.34941, 78.630006, 78.903929, 79.171334, 79.432371, 79.687184, 79.935918, 80.178713, 80.415708, 80.647035, 80.872827, 81.093214, 81.308321, 81.518272, 81.723188, 81.923187, 82.118384, 82.308893, 82.494824, 82.676285, 82.853382, 83.026219, 83.194896, 83.359512 };
            //Console.WriteLine(longtitudes11.Length);
            //int start = 60;
            //int end = start + 10;
            //for (int kk = start; kk < end; kk++)
            //{
            //    string currentToken = "099408";
            //    String long1 = "," + longtitudes11[kk] + ",";
            //    String long2 = "," + longtitudes11[kk + 1];
            //    double lat1 = -178.490775;
            //    double deltaLat1 = 2.5052;
            //    for (i = 66; i < 120; i++)
            //    {

            //        try
            //        {
            //            using (WebClient client = new WebClient())
            //            {

            //                String currentUrl = "https://render.openstreetmap.org/cgi-bin/export?bbox=" + lat1.ToString() + long1 + (lat1 + deltaLat1).ToString() + long2 + "&scale=2000000&format=svg";
            //                Console.WriteLine(currentUrl);
            //                Uri url = new Uri(currentUrl);
            //                client.Headers.Add(HttpRequestHeader.Authorization, "render.openstreetmap.org");
            //                client.Headers.Add("method", "GET");
            //                client.Headers.Add("path", "/cgi-bin/export?bbox=28.83746292791811,59.63284874301492,30.49090531073061,60.26414816040228&scale=250000&format=svg");
            //                client.Headers.Add("scheme", "https");
            //                client.Headers.Add(HttpRequestHeader.Accept, "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9");
            //                //client.Headers.Add(HttpRequestHeader.AcceptEncoding, "gzip, deflate, br");
            //                client.Headers.Add(HttpRequestHeader.AcceptLanguage, "ru-RU,ru;q=0.9,en-US;q=0.8,en;q=0.7");
            //                client.Headers.Add(HttpRequestHeader.Cookie, "_osm_totp_token=" + currentToken);
            //                client.Headers.Add("sec-ch-ua", "\"Chromium\";v=\"88\", \"Google Chrome\";v=\"88\", \"; Not A Brand\";v=\"99\"");
            //                client.Headers.Add(HttpRequestHeader.Referer, "https://www.openstreetmap.org/");
            //                client.Headers.Add("sec-fetch-dest", "document");
            //                client.Headers.Add("sec-fetch-mode", "navigate");
            //                client.Headers.Add("sec-fetch-site", "same-site");
            //                client.Headers.Add("sec-fetch-user", "?1");
            //                client.Headers.Add("upgrade-insecure-requests", "1");
            //                client.Headers.Add(HttpRequestHeader.UserAgent, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.190 Safari/537.36");
            //                client.QueryString.Add("bbox", "104.49886322021486,41.725461744125646,104.64717864990236,41.951064612666684");
            //                client.QueryString.Add("scale", "250000");
            //                client.QueryString.Add("format", "svg");
            //                Console.WriteLine(i);
            //                client.DownloadFile(url, i.ToString() + "_" + kk.ToString() + ".svg");
            //                lat1 += deltaLat1;

            //            }
            //        }
            //        catch (Exception e)
            //        {
            //            Console.WriteLine(e);
            //            System.Threading.Thread.Sleep(5000);
            //            String currentUrl = "https://www.openstreetmap.org/#map=8/41.8368/104.5450&layers=N";
            //            HttpWebRequest tQ = (HttpWebRequest)HttpWebRequest.Create(currentUrl);
            //            tQ.Accept = "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9";
            //            tQ.UserAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.41 YaBrowser/21.2.0.1097 Yowser/2.5 Safari/537.36";
            //            tQ.ContentType = "text/html; charset=utf-8";
            //            tQ.Referer = currentUrl;
            //            HttpWebResponse tS;

            //            tS = (HttpWebResponse)tQ.GetResponse();
            //            string tC = tS.Headers["Set-Cookie"];
            //            var cc = tC.IndexOf("_osm_totp_token=");
            //            currentToken = tC.Substring(cc + "_osm_totp_token=".Length, 6);
            //            //string num = tC.Trim(, 2);
            //            Console.WriteLine(tC);
            //            i = i - 1;
            //        }

            //        Console.WriteLine("i=" + i.ToString());
            //    }

            //}


            //int ggg = 0;
        }
    }
}
