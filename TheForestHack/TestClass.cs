using System;
using System.Runtime.InteropServices;

namespace TheForestHack {

    public class TestClass {

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool AllocConsole();
        
        public static int TestMethod(String parameter) {
            AllocConsole();
            Kernel32.SystemInfo systemInfo = new Kernel32.SystemInfo();
            Kernel32.GetSystemInfo(out systemInfo);
            Console.WriteLine("Min Addr:" + systemInfo.lpMinimumApplicationAddress.ToInt64());
            Console.WriteLine("Max Addr:" + systemInfo.lpMaximumApplicationAddress.ToInt64());
            return 0;
        }
        
    }
    
}