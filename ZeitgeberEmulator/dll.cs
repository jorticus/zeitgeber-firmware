using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace Zeitgeber
{
    #region Delegates

    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void onTestDelegate(int x);

    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void onDisplayUpdateDelegate(IntPtr screen, UInt16 w, UInt16 h);

    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void TaskProc();

    #endregion


    [StructLayout(LayoutKind.Sequential)]
    public struct HardwareStatus
    {
        public byte ol_power;
        public byte ol_reset;
        public byte btn1;
        public byte btn2;
        public byte btn3;
        public byte btn4;
        public byte led1;
        public byte led2;
        public byte motor;
        public byte peizo;
        public byte vbus_sense;
        public byte inta;
        public byte intm;
        public byte pw_stat1;
        public byte pw_stat2;
        public byte pw_ce;
        public byte bt_reset;
        public UInt16 an_vbat;
        public UInt16 an_light;
    }

    public enum TaskState { tsStop=0, tsIdle, tsRun }

    [StructLayout(LayoutKind.Sequential, Size=17)]
    public struct Task
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst=7)] // C# needs an extra byte for the NULL char
        public string name;
        private TaskProc proc;
        public TaskState state;
        public UInt16 interval;
        public UInt16 cpu_time;
        public UInt16 next_run;
        public UInt16 ticks;
    }

    public class dll
    {
        public const string DLL_NAME = "C:\\Users\\Jared\\Documents\\Projects\\PIC\\MPLABX\\Zeitgeber.X\\Debug\\zeitgeber.dll";


        #region Private Methods
        // Private methods here have wrappers defined which make
        // them easier to call from C#


        //[DllImport(DLL_NAME, CallingConvention = CallingConvention.StdCall)]
        //private static extern uint zGetSchedulerTasks(ref IntPtr tasks);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.StdCall)]
        private static extern UInt16 zGetNumTasks();

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.StdCall)]
        private static extern IntPtr zGetTask(UInt16 index);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.StdCall)]
        private static extern void zGetHardwareStatus(ref HardwareStatus status);

        #endregion

        #region Methods
        // Methods here can be called directly from C#


        [DllImport(DLL_NAME, EntryPoint="zInitialize", CallingConvention = CallingConvention.StdCall)]
        public static extern void Initialize();

        [DllImport(DLL_NAME, EntryPoint="zProcess", CallingConvention = CallingConvention.StdCall)]
        public static extern void Process();

        [DllImport(DLL_NAME, EntryPoint="zUpdateButton", CallingConvention = CallingConvention.StdCall)]
        public static extern void UpdateButton(byte idx, bool state);

        [DllImport(DLL_NAME, EntryPoint = "zSetSystick", CallingConvention = CallingConvention.StdCall)]
        public static extern void SetSystick(UInt16 systick);


        #endregion

        #region Callbacks

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.StdCall)]
        public static extern void set_onDisplayUpdate(onDisplayUpdateDelegate cb);

        #endregion


        #region Wrappers
        public static HardwareStatus GetHardwareStatus()
        {
            HardwareStatus status = new HardwareStatus();
            zGetHardwareStatus(ref status);
            return status;
        }

        public static Task[] GetSchedulerTasks()
        {
            UInt16 num = zGetNumTasks();
            Task[] tasks = new Task[num];

            for (UInt16 i = 0; i < num; i++)
            {
                IntPtr buf = zGetTask(i);
                if (buf != IntPtr.Zero)
                {
                    Task task = (Task)Marshal.PtrToStructure(buf, typeof(Task));
                    tasks[i] = task;
                }
            }

            return tasks;
        }

        /*public static Task[] GetSchedulerTasks()
        {
            IntPtr rawTasks = IntPtr.Zero;
            uint num = zGetSchedulerTasks(ref rawTasks);

            Debug.WriteLine("GetSchedulerTasks (num:{0})", num);

            // Marshal the screen buffer into a C# array
            Task[] tasks = new Task[num];
            int size = Marshal.SizeOf(tasks);

            Marshal.Copy(rawTasks, tasks, 0, size);
            Marshal.

            return tasks;
        }*/

        #endregion
    }

}
