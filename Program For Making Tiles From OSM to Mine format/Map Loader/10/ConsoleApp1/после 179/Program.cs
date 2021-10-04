using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            int i = 0;
            System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
            double[] longtitudes11 = new double[] { 38.822591, 39.368279, 39.909736, 40.446947, 40.979898, 41.508577, 42.032975, 42.55308, 43.068888, 43.580391, 44.087585, 44.590467, 45.089036, 45.58329, 46.073231, 46.55886, 47.040182, 47.5172, 47.989922, 48.458352, 48.922499, 49.382373, 49.837983, 50.289339, 50.736455, 51.179343, 51.618016, 52.05249, 52.48278, 52.908902, 53.330873, 53.748711, 54.162434, 54.572062, 54.977613, 55.37911, 55.776573, 56.170023, 56.559482, 56.944974, 57.326521, 57.704147, 58.077876, 58.447733, 58.813742, 59.175928, 59.534318, 59.888937, 60.239811, 60.586967, 60.930432, 61.270233, 61.606397, 61.93895, 62.267923, 62.593341, 62.915233, 63.233628, 63.548552, 63.860036, 64.168107, 64.472794, 64.774125, 65.07213, 65.366837, 65.658274, 65.946472, 66.231457, 66.51326, 66.791909, 67.067433, 67.339861, 67.60922, 67.875541, 68.138852, 68.39918, 68.656555, 68.911005, 69.162558, 69.411243, 69.657086, 69.900118, 70.140365, 70.377854, 70.612614, 70.844672, 71.074057, 71.300793, 71.524909, 71.746432, 71.965388, 72.181803, 72.395706, 72.60712, 72.816073, 73.022592, 73.2267, 73.428424, 73.627789, 73.82482, 74.019543, 74.211983, 74.402163, 74.590108, 74.775843, 74.959392, 75.140778, 75.320025, 75.497157, 75.672198, 75.845168, 76.016094, 76.184995, 76.351896, 76.516819, 76.679785, 76.840817, 76.999935, 77.157163, 77.31252, 77.466029, 77.617709, 77.767582, 77.915669, 78.061989, 78.206563, 78.34941, 78.490552, 78.630006, 78.767792, 78.903929, 79.038438, 79.171334, 79.30264, 79.432371, 79.560546, 79.687184, 79.812302, 79.935918, 80.05805, 80.178713, 80.297927, 80.415708, 80.532071, 80.647035, 80.760615, 80.872827, 80.983688, 81.093214, 81.20142, 81.308321, 81.413933, 81.518272, 81.621352, 81.723188, 81.823794, 81.923187, 82.021378, 82.118384, 82.214217, 82.308893};
            Console.WriteLine(longtitudes11.Length);
            int start = 0;
            M:int end = start + 160;
            for (int kk = start; kk < end; kk++)
            {
                string currentToken = "785799";
                String long1 = "," + longtitudes11[kk] + ",";
                String long2 = "," + longtitudes11[kk + 1];
                double lat1 = -180.00000000;
                double deltaLat1 = 0.256625;
                //double lat1 = -179.743375;
                //double deltaLat1 = 1.2526;
                for (i = 128; i < 129; i++)
                {

                    try
                    {
                        using (WebClient client = new WebClient())
                        {

                            String currentUrl = "https://render.openstreetmap.org/cgi-bin/export?bbox=" + lat1.ToString() + long1 + (lat1 + deltaLat1).ToString() + long2 + "&scale=1000000&format=svg";
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
                        catch(Exception eee)
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
                        i = i - 1;
                    }

                    Console.WriteLine("i=" + i.ToString());
                }

            }


            int ggg = 0;
        }
    }
}
