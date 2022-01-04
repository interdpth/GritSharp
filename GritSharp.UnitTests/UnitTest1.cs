using System;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace GritSharp.UnitTests
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestMethod1()




        {
            var p = new GritSharp();
            List<byte> testArray = new List<byte>();

            for(int i =0;i<126;i++)
            {
                testArray.Add(0x10);
            }

            var b = new Random(new Random(10).Next(0, 0xFFFF)).Next(0, 255);
            for (int i = 0; i < 126; i++)
            {
                testArray.Add((byte)b);
            }

            for (int i = 0; i < 126; i++)
            {
                testArray.Add(0x20);
            }

            var c = new Random(new Random(10).Next(0, 0xFFFF)).Next(0, 255);
            for (int i = 0; i < 126; i++)
            {
                testArray.Add((byte)c);
            }

            var test = p.GBARLEComp(testArray.ToArray());
            Console.WriteLine("");
        }
    }
}
