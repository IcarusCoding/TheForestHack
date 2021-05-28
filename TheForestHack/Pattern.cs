using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace TheForestHack {
    
    public sealed class Pattern {

        private readonly IntPtr _processPtr;
        
        public Pattern(string process, string pattern) { 
            Process[] processes = Process.GetProcessesByName(process);
            if (processes.Length == 0) {
                Console.WriteLine("Could not find a process with name " + process + ".");
                return;
            }

            if (processes.Length != 1) {
                Console.WriteLine("Could not find unique process name " + process + ".");
                return;
            }
            Console.WriteLine("Found process with name " + process + ".");
            _processPtr = Kernel32.OpenProcess(Kernel32.ProcessAccessRights.ProcessAllAccess, false, processes[0].Id);
        }

    }
    
}