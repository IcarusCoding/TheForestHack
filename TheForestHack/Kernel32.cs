using System;
using System.Runtime.InteropServices;

namespace TheForestHack {
    
    public class Kernel32 {
        
        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern IntPtr OpenProcess(ProcessAccessRights dwDesiredAccess, bool bInheritHandle, int dwProcessId);

        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern bool ReadProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, int nSize, out IntPtr lpNumberOfBytesRead);
        
        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern void GetSystemInfo(out SystemInfo lpSystemInfo);

        public enum ProcessAccessRights {
            ProcessAllAccess = 0x001F0FFF,
            ProcessCreateProcess = 0x00000080,
            ProcessCreateThread = 0x00000002,
            ProcessDupHandle = 0x00000040,
            ProcessQueryInformation = 0x00000400,
            ProcessQueryLimitedInformation = 0x00001000,
            ProcessSetInformation = 0x00000200,
            ProcessSetQuota = 0x00000100,
            ProcessSuspendResume = 0x00000800,
            ProcessTerminate = 0x00000001,
            ProcessVmOperation = 0x00000008,
            ProcessVmRead = 0x00000010,
            ProcessVmWrite = 0x00000020,
            Synchronize = 0x00100000
        }
        
        [StructLayout(LayoutKind.Sequential)]
        public struct SystemInfo {
            public ushort wProcessorArchitecture;
            public ushort wReserved;
            public uint dwPageSize;
            public IntPtr lpMinimumApplicationAddress;
            public IntPtr lpMaximumApplicationAddress;
            public IntPtr dwActiveProcessorMask;
            public uint dwNumberOfProcessors;
            public uint dwProcessorType;
            public uint dwAllocationGranularity;
            public ushort wProcessorLevel;
            public ushort wProcessorRevision;
        }
        
    }
    
}