using HtmlAgilityPack;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TranscriptParser
{
    class Program
    {
        static Ders ParseDers(HtmlNodeCollection sutunlar)
        {
            Ders retVal = new Ders();
            retVal.Kodu = sutunlar[0].InnerText.Trim();
            retVal.Isim = sutunlar[1].InnerText.Trim();
            retVal.ComuKredi = sutunlar[2].InnerText.Trim();
            retVal.AKTS = sutunlar[3].InnerText.Trim();
            retVal.Katsayi = sutunlar[4].InnerText.Trim();
            retVal.Sonuc = sutunlar[5].InnerText.Trim();
            return retVal;


        }
        static void Main(string[] args)
        {
            if(args.Length == 0)
            {
                Console.WriteLine("No Arguments");
                Console.ReadKey();
                return;
            }
            string html = File.ReadAllText(args[0]);
            string ogrenciNumara;
            List<Ders> parsedDersler = ParseTranscript(html, out ogrenciNumara);
            TextDosyaYaz(parsedDersler, ogrenciNumara);
        }

        private static void TextDosyaYaz(List<Ders> parsedDersler, string ogrenciNumara)
        {
            using (var fs = File.OpenWrite(ogrenciNumara + ".txt"))
            {
                using (var sw = new StreamWriter(fs))
                {
                    foreach (var ders in parsedDersler)
                    {
                        sw.WriteLine("{0}\t{1}\t{2}",
                            ders.Kodu.Replace("\t", " "),
                            ogrenciNumara.Replace("\t", " "),
                            ders.Sonuc.Replace("\t", " ")
                        );
                    }
                }
            }
        }

        private static List<Ders> ParseTranscript(string html, out string ogrenciNumara)
        {
            List<Ders> parsedDersler = new List<TranscriptParser.Ders>();
            HtmlDocument doc = new HtmlDocument();
            doc.LoadHtml(html);
            var dersler = doc.DocumentNode.SelectNodes("//tr[starts-with(@id,'ctl00_content_RadDock1_C_dlRapor_')]");
            //doc.DocumentNode.SelectNodes("//table[@id='ctl00_content_RadDock1_C_dlRapor']/tbody/tr/td/div/table/tbody/tr");
            ogrenciNumara = string.Join("", doc.DocumentNode.SelectNodes("//*[@id='ctl00_content_RadDock1_C_trOgrenciNumarasi']/td")[1].InnerText.Where(c => char.IsDigit(c)).ToArray());
            foreach (var ders in dersler)
                parsedDersler.Add(ParseDers(ders.SelectNodes("td")));
            return parsedDersler;
        }
    }
}
