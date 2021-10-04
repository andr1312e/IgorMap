using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace MapDowloader5
{
    class Program
    {
        static void Main(string[] args)
        {
            int i = 0;
            System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
            double[] longtitudes11 = new double[] { 38.822591, 54.162434, 65.366837, 73.2267, 78.630006, 82.308893};
            Console.WriteLine(longtitudes11.Count());
            int start = 0;
            int end = start + 6;
             M: for (int kk = start; kk < end; kk++)
            {
                string currentToken = "579687";
                String long1 = "," + longtitudes11[kk] + ",";
                String long2 = "," + longtitudes11[kk + 1];
                double lat1 = 18.671225;
                double deltaLat1 = 0.6263 * 64;
                for (i = 0; i < 5; i++)
                {
                    try
                    {
                        using (WebClient client = new WebClient())
                        {
                            String currentUrl = "https://render.openstreetmap.org/cgi-bin/export?bbox=" + lat1.ToString() + long1 + (lat1 + deltaLat1).ToString() + long2 + "&scale=32000000&format=svg";
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


            //int ggg = 0;

            //ПОЛОСОЧКА у 180
        //     int i = 0;
        //     System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
        //     double[] longtitudes11 = new double[] { 38.822591, 54.162434, 65.366837, 73.2267, 78.630006, 82.308893 };
        //     Console.WriteLine(longtitudes11.Count());
        //     int start = 3;
        //     int end = start + 5;
        // M: for (int kk = start; kk < end; kk++)
        //     {
        //         string currentToken = "277262";
        //         String long1 = "," + longtitudes11[kk] + ",";
        //         String long2 = "," + longtitudes11[kk + 1];
        //         double lat1 = -140.912775;
        //         double deltaLat1 = 40.0832;
        //         for (i = 5; i < 7; i++)
        //         {
        //             try
        //             {
        //                 using (WebClient client = new WebClient())
        //                 {
        //                     String currentUrl = "https://render.openstreetmap.org/cgi-bin/export?bbox=" + lat1.ToString() + long1 + (lat1+deltaLat1).ToString() + long2 + "&scale=32000000&format=svg";
        //                     Uri url = new Uri(currentUrl);
        //                     client.Headers.Add(HttpRequestHeader.Authorization, "render.openstreetmap.org");
        //                     client.Headers.Add("method", "GET");
        //                     client.Headers.Add("path", "/cgi-bin/export?bbox=28.83746292791811,59.63284874301492,30.49090531073061,60.26414816040228&scale=250000&format=svg");
        //                     client.Headers.Add("scheme", "https");
        //                     client.Headers.Add(HttpRequestHeader.Accept, "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9");
        //                     //client.Headers.Add(HttpRequestHeader.AcceptEncoding, "gzip, deflate, br");
        //                     client.Headers.Add(HttpRequestHeader.AcceptLanguage, "ru-RU,ru;q=0.9,en-US;q=0.8,en;q=0.7");
        //                     client.Headers.Add(HttpRequestHeader.Cookie, "_osm_totp_token=" + currentToken);
        //                     client.Headers.Add("sec-ch-ua", "\"Chromium\";v=\"88\", \"Google Chrome\";v=\"88\", \"; Not A Brand\";v=\"99\"");
        //                     client.Headers.Add(HttpRequestHeader.Referer, "https://www.openstreetmap.org/");
        //                     client.Headers.Add("sec-fetch-dest", "document");
        //                     client.Headers.Add("sec-fetch-mode", "navigate");
        //                     client.Headers.Add("sec-fetch-site", "same-site");
        //                     client.Headers.Add("sec-fetch-user", "?1");
        //                     client.Headers.Add("upgrade-insecure-requests", "1");
        //                     client.Headers.Add(HttpRequestHeader.UserAgent, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.190 Safari/537.36");
        //                     client.QueryString.Add("bbox", "104.49886322021486,41.725461744125646,104.64717864990236,41.951064612666684");
        //                     client.QueryString.Add("scale", "250000");
        //                     client.QueryString.Add("format", "svg");
        //                     Console.WriteLine(i);
        //                     client.DownloadFile(url, i.ToString() + "_" + kk.ToString() + ".svg");
        //
        //                 }
        //
        //             }
        //             catch (Exception e)
        //             {
        //                 Console.WriteLine(e);
        //                 i--;
        //                 lat1 -= deltaLat1;
        //                 System.Threading.Thread.Sleep(5000);
        //                 String currentUrl = "https://www.openstreetmap.org/#map=12/41.8368/104.5450&layers=N";
        //                 HttpWebRequest tQ = (HttpWebRequest)HttpWebRequest.Create(currentUrl);
        //                 tQ.Accept = "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9";
        //                 tQ.UserAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.41 YaBrowser/21.2.0.1097 Yowser/2.5 Safari/537.36";
        //                 tQ.ContentType = "text/html; charset=utf-8";
        //                 tQ.Referer = currentUrl;
        //                 HttpWebResponse tS;
        //                 try
        //                 {
        //                     tS = (HttpWebResponse)tQ.GetResponse();
        //                 }
        //                 catch (Exception eee)
        //                 {
        //                     start = start + 2;
        //                     Console.WriteLine(eee);
        //                     Console.WriteLine("goto");
        //                     goto M;
        //                 }
        //                 string tC = tS.Headers["Set-Cookie"];
        //                 var cc = tC.IndexOf("_osm_totp_token=");
        //                 currentToken = tC.Substring(cc + "_osm_totp_token=".Length, 6);
        //                 //string num = tC.Trim(, 2);
        //                 Console.WriteLine(tC);
        //             }
        //             lat1 += deltaLat1;
        //             Console.WriteLine("i=" + i.ToString());
        //         }
        //
        //     }
        //
        //
        //     int ggg = 0;
        }
    }
}
