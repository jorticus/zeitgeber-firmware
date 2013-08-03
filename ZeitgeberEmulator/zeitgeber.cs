using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Runtime.InteropServices;

using ZeitgeberEmulator;
namespace Zeitgeber
{
    /*public class Zeitgeber
    {
        private void onTest(int x)
        {
            Debug.WriteLine("CB");
            Debug.WriteLine(x);
        }

        private void onDisplayUpdate(IntPtr buf, uint w, uint h)
        {
            // Marshal the screen buffer into a C# array
            int size = (int)(w * h);
            byte[] screen = new byte[size];
            Marshal.Copy(buf, screen, 0, size);

            // Update the virtual OLED display
            //...
        }

        public Zeitgeber()
        {
            dll.set_onDisplayUpdate(new dll.onDisplayUpdateDelegate(this.onDisplayUpdate));
        }

    }*/
}
