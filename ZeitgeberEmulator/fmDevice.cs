using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Zeitgeber;
using System.Runtime.InteropServices;
using System.Diagnostics;
namespace ZeitgeberEmulator
{
    public partial class fmDevice : Form
    {
        public delegate void onDisplayUpdateDelegate(IntPtr buf, uint w, uint h);

        public fmDevice()
        {
            InitializeComponent();

            
            
        }

        public void onDisplayUpdate(IntPtr buf, UInt16 w, UInt16 h)
        {
            //Debug.WriteLine("** Display Update ({0},{1})", w, h);

            // Marshal the screen buffer into a C# array
            int size = (int)(w * h * 2);
            byte[] screen = new byte[size];
            Marshal.Copy(buf, screen, 0, size);

            // Convert the screen buffer to a Bitmap
            Bitmap bmp = new Bitmap(w, h);
            int x, y;
            int i = 0;
            for (y = 0; y < h; y++)
            {
                for (x = 0; x < w; x++)
                {
                    // Convert 16-bit color (5:6:5) format to R,G,B
                    UInt16 color = (UInt16)((UInt16)screen[i] | (UInt16)screen[i + 1] << 8);
                    i += 2;

                    byte r = (byte)(((color & 0xF800) >> 11) * 255 / 31);
                    byte g = (byte)(((color & 0x07E0) >> 5) * 255 / 60);
                    byte b = (byte)((color & 0x001F) * 255 / 31);
                    bmp.SetPixel(x, y, Color.FromArgb(r,g,b));
                }
            }

            // Draw the bitmap to the virtual OLED display
            OLED.Image = bmp;
            OLED.Invalidate();
        }


        private void fmDevice_Load(object sender, EventArgs e)
        {
        }

        private void fmDevice_Shown(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {

        }

        private void fmDevice_FormClosed(object sender, FormClosedEventArgs e)
        {
            
        }

        private void fmDevice_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Hide();
            e.Cancel = true;
        }

        private void btn1_MouseDown(object sender, MouseEventArgs e)
        {
            dll.UpdateButton(1, true);
        }

        private void btn1_MouseUp(object sender, MouseEventArgs e)
        {
            dll.UpdateButton(1, false);
        }

        private void btn2_MouseDown(object sender, MouseEventArgs e)
        {
            dll.UpdateButton(2, true);
        }

        private void btn2_MouseUp(object sender, MouseEventArgs e)
        {
            dll.UpdateButton(2, false);
        }

        private void btn3_MouseDown(object sender, MouseEventArgs e)
        {
            dll.UpdateButton(3, true);
        }

        private void btn3_MouseUp(object sender, MouseEventArgs e)
        {
            dll.UpdateButton(3, false);
        }

        private void btn4_MouseDown(object sender, MouseEventArgs e)
        {
            dll.UpdateButton(4, true);
        }

        private void btn4_MouseUp(object sender, MouseEventArgs e)
        {
            dll.UpdateButton(4, false);
        }
    }
}
