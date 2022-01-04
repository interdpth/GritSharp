using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace GritSharp
{
    public class GritSharp
    {
        [StructLayout(LayoutKind.Sequential)]
        public partial struct RECORD
        {
            public int width;
            public int height;
            public byte[] data;        
        }

        [DllImport("GritNative.dll")]
        public static extern IntPtr InitGrit();




        [DllImport("GritNative.dll")]
        public static extern void SetSource(IntPtr ret, string tstring);


        //-gb -gB 16 -ftbin
        [DllImport("GritNative.dll")]
        public static extern void SetBitmapMode(IntPtr ret);

        [DllImport("GritNative.dll")]
        public static extern IntPtr Convert( string ret);


        [DllImport("GritNative.dll")]
        public static extern IntPtr GetBitmap(IntPtr ret);

        [DllImport("GritNative.dll")]
        public static extern Int32 GetBitmapLen(IntPtr ret);

        [DllImport("GritNative.dll")]
        public static extern  void RLECOmpress(byte[] src, int len, ref RECORD rec); 
        private IntPtr _gritRecord;


        //for test tlib  -gb -gB 16 -ftbin
        public GritSharp()
        {

            //_gritRecord = InitGrit();
        }

        public void ToggleBitmap()
        {
           // SetBitmapMode(_gritRecord);
        }

        public void SetImage(string path)
        {
           // SetSource(_gritRecord, path);
        }
        public IntPtr Export(string path)
        {
            _gritRecord= Convert(path);
            return _gritRecord;
        }
        public byte[] GetData()
        {
            int len = GetBitmapLen(_gritRecord);
            byte[] dat = new byte[len*2];
            Marshal.Copy(GetBitmap(_gritRecord), dat, 0, len * 2);


            return dat;
        }


        public  byte[] GBARLEComp(byte[] data)
        {
            RECORD newRecord = new RECORD();
            RLECOmpress(data, data.Length, ref newRecord);

            byte[] returnv= newRecord.data;

            Console.WriteLine("Debug");
            return returnv;

        }
    }
}
