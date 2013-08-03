namespace ZeitgeberEmulator
{
    partial class fmDevice
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.OLED = new System.Windows.Forms.PictureBox();
            this.btn1 = new System.Windows.Forms.Button();
            this.btn2 = new System.Windows.Forms.Button();
            this.btn3 = new System.Windows.Forms.Button();
            this.btn4 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.OLED)).BeginInit();
            this.SuspendLayout();
            // 
            // OLED
            // 
            this.OLED.BackColor = System.Drawing.Color.Black;
            this.OLED.Location = new System.Drawing.Point(46, 33);
            this.OLED.Name = "OLED";
            this.OLED.Size = new System.Drawing.Size(128, 128);
            this.OLED.TabIndex = 0;
            this.OLED.TabStop = false;
            // 
            // btn1
            // 
            this.btn1.Location = new System.Drawing.Point(188, 13);
            this.btn1.Name = "btn1";
            this.btn1.Size = new System.Drawing.Size(21, 44);
            this.btn1.TabIndex = 1;
            this.btn1.UseVisualStyleBackColor = true;
            this.btn1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.btn1_MouseDown);
            this.btn1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.btn1_MouseUp);
            // 
            // btn2
            // 
            this.btn2.Location = new System.Drawing.Point(188, 164);
            this.btn2.Name = "btn2";
            this.btn2.Size = new System.Drawing.Size(21, 44);
            this.btn2.TabIndex = 2;
            this.btn2.UseVisualStyleBackColor = true;
            this.btn2.MouseDown += new System.Windows.Forms.MouseEventHandler(this.btn2_MouseDown);
            this.btn2.MouseUp += new System.Windows.Forms.MouseEventHandler(this.btn2_MouseUp);
            // 
            // btn3
            // 
            this.btn3.Location = new System.Drawing.Point(12, 164);
            this.btn3.Name = "btn3";
            this.btn3.Size = new System.Drawing.Size(21, 44);
            this.btn3.TabIndex = 3;
            this.btn3.UseVisualStyleBackColor = true;
            this.btn3.MouseDown += new System.Windows.Forms.MouseEventHandler(this.btn3_MouseDown);
            this.btn3.MouseUp += new System.Windows.Forms.MouseEventHandler(this.btn3_MouseUp);
            // 
            // btn4
            // 
            this.btn4.Location = new System.Drawing.Point(12, 12);
            this.btn4.Name = "btn4";
            this.btn4.Size = new System.Drawing.Size(21, 44);
            this.btn4.TabIndex = 4;
            this.btn4.UseVisualStyleBackColor = true;
            this.btn4.MouseDown += new System.Windows.Forms.MouseEventHandler(this.btn4_MouseDown);
            this.btn4.MouseUp += new System.Windows.Forms.MouseEventHandler(this.btn4_MouseUp);
            // 
            // fmDevice
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = global::ZeitgeberEmulator.Properties.Resources.background2;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.ClientSize = new System.Drawing.Size(229, 220);
            this.Controls.Add(this.btn4);
            this.Controls.Add(this.btn3);
            this.Controls.Add(this.btn2);
            this.Controls.Add(this.btn1);
            this.Controls.Add(this.OLED);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.MaximizeBox = false;
            this.Name = "fmDevice";
            this.ShowIcon = false;
            this.Text = "Zeitgeber";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.fmDevice_FormClosing);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.fmDevice_FormClosed);
            this.Load += new System.EventHandler(this.fmDevice_Load);
            this.Shown += new System.EventHandler(this.fmDevice_Shown);
            ((System.ComponentModel.ISupportInitialize)(this.OLED)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox OLED;
        private System.Windows.Forms.Button btn1;
        private System.Windows.Forms.Button btn2;
        private System.Windows.Forms.Button btn3;
        private System.Windows.Forms.Button btn4;
    }
}