using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace mapDownloader11
{
    class Program
    {
        static void Main(string[] args)
        {
            int i = 0;
            System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
            double[] longtitudes11 = new double[] { 38.822591,  39.095963,  39.368279,  39.639537,  39.909736,  40.178873,  40.446947,  40.713956,  40.979898,  41.244773,  41.508577,  41.771312,  42.032975,  42.293564,  42.55308,  42.811522,  43.068888,  43.325178,  43.580391,  43.834527,  44.087585,  44.339565,  44.590467,  44.840291,  45.089036,  45.336702,  45.58329,  45.828799,  46.073231,  46.316584,  46.55886,  46.80006,  47.040182,  47.279229,  47.5172,  47.754098,  47.989922,  48.224673,  48.458352,  48.69096,  48.922499,  49.15297,  49.382373,  49.61071,  49.837983,  50.064192,  50.289339,  50.513427,  50.736455,  50.958427,  51.179343,  51.399206,  51.618016,  51.835778,  52.05249,  52.268157,  52.48278,  52.696361,  52.908902,  53.120405,  53.330873,  53.540308,  53.748711,  53.956085,  54.162434,  54.367758,  54.572062,  54.775346,  54.977613,  55.178868,  55.37911,  55.578345,  55.776573,  55.973798,  56.170023,  56.36525,  56.559482,  56.752723,  56.944974,  57.136239,  57.326521,  57.515823,  57.704147,  57.891497,  58.077876,  58.263287,  58.447733,  58.631216,  58.813742,  58.995311,  59.175928,  59.355596,  59.534318,  59.712097,  59.888937,  60.06484,  60.239811,  60.413853,  60.586967,  60.759159,  60.930432,  61.100789,  61.270233,  61.438767,  61.606397,  61.773123,  61.93895,  62.103883,  62.267923,  62.431074,  62.593341,  62.754726,  62.915233,  63.074866,  63.233628,  63.391522,  63.548552,  63.704723,  63.860036,  64.014496,  64.168107,  64.320872,  64.472794,  64.623877,  64.774125,  64.923542,  65.07213,  65.219894,  65.366837,  65.512963,  65.658274,  65.802777,  65.946472,  66.089364,  66.231457,  66.372755,  66.51326,  66.652977,  66.791909,  66.93006,  67.067433,  67.204033,  67.339861,  67.474922,  67.60922,  67.742759,  67.875541,  68.007571,  68.138852,  68.269387,  68.39918,  68.528235,  68.656555,  68.784144,  68.911005,  69.037142,  69.162558,  69.287257,  69.411243,  69.534518,  69.657086,  69.778952,  69.900118,  70.020587,  70.140365,  70.259452,  70.377854,  70.495574,  70.612614,  70.72898,  70.844672,  70.959697,  71.074057,  71.187754,  71.300793,  71.413177,  71.524909,  71.635993,  71.746432,  71.856229,  71.965388,  72.073911,  72.181803,  72.289067,  72.395706,  72.501722,  72.60712,  72.711903,  72.816073,  72.919636,  73.022592,  73.124945,  73.2267,  73.327858,  73.428424,  73.528399,  73.627789,  73.726594,  73.82482,  73.922469,  74.019543,  74.116047,  74.211983,  74.307354,  74.402163,  74.496413,  74.590108,  74.68325,  74.775843,  74.867889,  74.959392,  75.050353,  75.140778,  75.230667,  75.320025,  75.408854,  75.497157,  75.584937,  75.672198,  75.75894,  75.845168,  75.930885,  76.016094,  76.100796,  76.184995,  76.268695,  76.351896,  76.434604,  76.516819,  76.598545,  76.679785,  76.760541,  76.840817,  76.920614,  76.999935,  77.078784,  77.157163,  77.235073,  77.31252,  77.389504,  77.466029,  77.542096,  77.617709,  77.69287,  77.767582,  77.841848,  77.915669,  77.989049,  78.061989,  78.134493,  78.206563,  78.278202,  78.34941,  78.420193,  78.490552,  78.560488,  78.630006,  78.699106,  78.767792,  78.836065,  78.903929,  78.971386,  79.038438,  79.105086,  79.171334,  79.237185,  79.30264,  79.367701,  79.432371,  79.496652,  79.560546,  79.624057,  79.687184,  79.749932,  79.812302,  79.874297,  79.935918,  79.997168,  80.05805,  80.118564,  80.178713,  80.2385,  80.297927,  80.356996,  80.415708,  80.474065,  80.532071,  80.589727,  80.647035,  80.703997,  80.760615,  80.816891,  80.872827,  80.928426,  80.983688,  81.038617,  81.093214,  81.147481,  81.20142,  81.255032,  81.308321,  81.361287,  81.413933,  81.466261,  81.518272,  81.569968,  81.621352,  81.672424,  81.723188,  81.773643,  81.823794,  81.873641,  81.923187,  81.972431,  82.021378,  82.070028,  82.118384,  82.166446,  82.214217,  82.261699,  82.308893,  82.3558,  82.402423,  82.448764,  82.494824,  82.540604,  82.586106,  82.631333,  82.676285,  82.720964,  82.765373,  82.809512,  82.853382,  82.896987,  82.940327,  82.983404,  83.026219,  83.068774,  83.111071,  83.153111,  83.194896,  83.236427,  83.277705,  83.318733,  83.359512,  83.400042,  83.440327,  83.480366,  83.520163,  83.559717,  83.599031,  83.638105,  83.676943,  83.715544,  83.753911,  83.792044,  83.829945,  83.867616,  83.905058,  83.942272,  83.979259,  84.016022,  84.052561,  84.088878,  84.124973,  84.160849,  84.196507,  84.231948,  84.267172,  84.302183,  84.33698};
            Console.WriteLine(longtitudes11.Length);
            int start = 370;
            int end = start + 10;
            for (int kk = start; kk < end; kk++)
            {
                string currentToken = "099408";
                String long1 = "," + longtitudes11[kk] + ",";
                String long2 = "," + longtitudes11[kk + 1];
                double lat1 = 18.671225;
                double deltaLat1 = 0.6263;
                for (i = 0; i < 258; i++)
                {

                    try
                    {
                        using (WebClient client = new WebClient())
                        {

                            String currentUrl = "https://render.openstreetmap.org/cgi-bin/export?bbox=" + lat1.ToString() + long1 + (lat1 + deltaLat1).ToString() + long2 + "&scale=500000&format=svg";
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
        }
    }
}
