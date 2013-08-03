using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

using Zeitgeber;
namespace ZeitgeberEmulator
{
    static class Program
    {
        public static fmDevice fmDevice;
        public static fmMain fmMain;

        private static onDisplayUpdateDelegate _onDisplayUpdate;

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            fmDevice = new fmDevice();
            fmMain = new fmMain();

            InitializeEmulator();

            Application.Run(fmMain);
        }

        private static void InitializeEmulator()
        {
            // Assign GUI callbacks
            _onDisplayUpdate = new onDisplayUpdateDelegate(fmDevice.onDisplayUpdate);
            dll.set_onDisplayUpdate(_onDisplayUpdate);

            // Initialize (Virtual) Hardware
            dll.Initialize();

        }

        private static void ProcessEmulator()
        {
            dll.Process();
        }
    }
}
