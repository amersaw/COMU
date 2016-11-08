using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TranscriptParser
{

    /*
        <tr class="rgAltRow" id="ctl00_content_RadDock1_C_dlRapor_ctl00_rgYariyil_ctl00__3">
            <td>14BLM101</td>
            <td>Genel Fizik I</td>
            <td align="right">3,00</td>
            <td align="right">6,00</td>
            <td align="right">2,00</td>
            <td>CC</td>
        </tr>
     */
    class Ders
    {
        public string Kodu { get; set; }
        public string Isim { get; set; }
        public string ComuKredi { get; set; }
        public string AKTS { get; set; }
        public string Katsayi { get; set; }
        public string Sonuc { get; set; }
        public override string ToString()
        {
            return Kodu + " - " + Isim + " : " + Sonuc;
        }
    }
}
