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
            int layer = 4;
            System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
            M:
            for (int maxUp = 5; maxUp > 0; maxUp--)
            {
                using (WebClient client = new WebClient())
                {
                    String currentUrl = "https://www.netzwolf.info/osm/tilebrowser.html?tx=9&ty="+maxUp+"&tz=" + layer +"#tile";
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
                    Console.Write(acceptEncoding);
                }

            }
        }
    }
}
