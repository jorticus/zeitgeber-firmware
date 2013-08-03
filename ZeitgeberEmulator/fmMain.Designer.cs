namespace ZeitgeberEmulator
{
    partial class fmMain
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
            this.components = new System.ComponentModel.Container();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.lblSysFreq = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.tbSysFreq = new System.Windows.Forms.TrackBar();
            this.lblBatteryVoltage = new System.Windows.Forms.Label();
            this.cbCharging = new System.Windows.Forms.CheckBox();
            this.tbBatteryVoltage = new System.Windows.Forms.TrackBar();
            this.cbUsbPower = new System.Windows.Forms.CheckBox();
            this.cbBatteryPower = new System.Windows.Forms.CheckBox();
            this.btnShowDevice = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            this.label1 = new System.Windows.Forms.Label();
            this.checkBox2 = new System.Windows.Forms.CheckBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.listInfo = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.infoUpdateTimer = new System.Windows.Forms.Timer(this.components);
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.listTasks = new System.Windows.Forms.ListView();
            this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.lblSysTick = new System.Windows.Forms.Label();
            this.cbSlowTick = new System.Windows.Forms.CheckBox();
            this.tickTimer = new System.Windows.Forms.Timer(this.components);
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.tbSysFreq)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tbBatteryVoltage)).BeginInit();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.lblSysFreq);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.tbSysFreq);
            this.groupBox1.Controls.Add(this.lblBatteryVoltage);
            this.groupBox1.Controls.Add(this.cbCharging);
            this.groupBox1.Controls.Add(this.tbBatteryVoltage);
            this.groupBox1.Controls.Add(this.cbUsbPower);
            this.groupBox1.Controls.Add(this.cbBatteryPower);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(227, 204);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "System";
            // 
            // lblSysFreq
            // 
            this.lblSysFreq.Location = new System.Drawing.Point(10, 185);
            this.lblSysFreq.Name = "lblSysFreq";
            this.lblSysFreq.Size = new System.Drawing.Size(211, 16);
            this.lblSysFreq.TabIndex = 6;
            this.lblSysFreq.Text = "8 MHz";
            this.lblSysFreq.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 137);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(94, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "System Frequency";
            // 
            // tbSysFreq
            // 
            this.tbSysFreq.LargeChange = 1000;
            this.tbSysFreq.Location = new System.Drawing.Point(6, 153);
            this.tbSysFreq.Maximum = 32000;
            this.tbSysFreq.Minimum = 1000;
            this.tbSysFreq.Name = "tbSysFreq";
            this.tbSysFreq.Size = new System.Drawing.Size(215, 45);
            this.tbSysFreq.SmallChange = 100;
            this.tbSysFreq.TabIndex = 4;
            this.tbSysFreq.TickFrequency = 1000;
            this.tbSysFreq.Value = 8000;
            this.tbSysFreq.Scroll += new System.EventHandler(this.tbSysFreq_Scroll);
            // 
            // lblBatteryVoltage
            // 
            this.lblBatteryVoltage.Location = new System.Drawing.Point(10, 67);
            this.lblBatteryVoltage.Name = "lblBatteryVoltage";
            this.lblBatteryVoltage.Size = new System.Drawing.Size(211, 16);
            this.lblBatteryVoltage.TabIndex = 2;
            this.lblBatteryVoltage.Text = "3.40 V";
            this.lblBatteryVoltage.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // cbCharging
            // 
            this.cbCharging.AutoSize = true;
            this.cbCharging.Enabled = false;
            this.cbCharging.Location = new System.Drawing.Point(10, 109);
            this.cbCharging.Name = "cbCharging";
            this.cbCharging.Size = new System.Drawing.Size(68, 17);
            this.cbCharging.TabIndex = 3;
            this.cbCharging.Text = "Charging";
            this.cbCharging.UseVisualStyleBackColor = true;
            // 
            // tbBatteryVoltage
            // 
            this.tbBatteryVoltage.AutoSize = false;
            this.tbBatteryVoltage.LargeChange = 1000;
            this.tbBatteryVoltage.Location = new System.Drawing.Point(10, 35);
            this.tbBatteryVoltage.Maximum = 4800;
            this.tbBatteryVoltage.Name = "tbBatteryVoltage";
            this.tbBatteryVoltage.Size = new System.Drawing.Size(211, 29);
            this.tbBatteryVoltage.SmallChange = 100;
            this.tbBatteryVoltage.TabIndex = 2;
            this.tbBatteryVoltage.TickFrequency = 250;
            this.tbBatteryVoltage.Value = 3400;
            this.tbBatteryVoltage.Scroll += new System.EventHandler(this.tbBatteryVoltage_Scroll);
            // 
            // cbUsbPower
            // 
            this.cbUsbPower.AutoSize = true;
            this.cbUsbPower.Location = new System.Drawing.Point(10, 86);
            this.cbUsbPower.Name = "cbUsbPower";
            this.cbUsbPower.Size = new System.Drawing.Size(81, 17);
            this.cbUsbPower.TabIndex = 1;
            this.cbUsbPower.Text = "USB Power";
            this.cbUsbPower.UseVisualStyleBackColor = true;
            this.cbUsbPower.CheckedChanged += new System.EventHandler(this.cbUsbPower_CheckedChanged);
            // 
            // cbBatteryPower
            // 
            this.cbBatteryPower.AutoSize = true;
            this.cbBatteryPower.Checked = true;
            this.cbBatteryPower.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbBatteryPower.Location = new System.Drawing.Point(10, 19);
            this.cbBatteryPower.Name = "cbBatteryPower";
            this.cbBatteryPower.Size = new System.Drawing.Size(92, 17);
            this.cbBatteryPower.TabIndex = 0;
            this.cbBatteryPower.Text = "Battery Power";
            this.cbBatteryPower.UseVisualStyleBackColor = true;
            this.cbBatteryPower.CheckedChanged += new System.EventHandler(this.cbBatteryPower_CheckedChanged);
            // 
            // btnShowDevice
            // 
            this.btnShowDevice.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnShowDevice.Location = new System.Drawing.Point(133, 71);
            this.btnShowDevice.Name = "btnShowDevice";
            this.btnShowDevice.Size = new System.Drawing.Size(88, 23);
            this.btnShowDevice.TabIndex = 1;
            this.btnShowDevice.Text = "Show Device";
            this.btnShowDevice.UseVisualStyleBackColor = true;
            this.btnShowDevice.Click += new System.EventHandler(this.btnShowDevice_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.trackBar1);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.checkBox2);
            this.groupBox2.Controls.Add(this.checkBox1);
            this.groupBox2.Location = new System.Drawing.Point(12, 222);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(227, 124);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Sensors";
            // 
            // trackBar1
            // 
            this.trackBar1.AutoSize = false;
            this.trackBar1.Enabled = false;
            this.trackBar1.Location = new System.Drawing.Point(10, 83);
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Size = new System.Drawing.Size(211, 35);
            this.trackBar1.TabIndex = 3;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(10, 67);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(71, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Ambient Light";
            // 
            // checkBox2
            // 
            this.checkBox2.AutoSize = true;
            this.checkBox2.Enabled = false;
            this.checkBox2.Location = new System.Drawing.Point(10, 42);
            this.checkBox2.Name = "checkBox2";
            this.checkBox2.Size = new System.Drawing.Size(136, 17);
            this.checkBox2.TabIndex = 1;
            this.checkBox2.Text = "Magnetometer Enabled";
            this.checkBox2.UseVisualStyleBackColor = true;
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Enabled = false;
            this.checkBox1.Location = new System.Drawing.Point(10, 19);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(136, 17);
            this.checkBox1.TabIndex = 0;
            this.checkBox1.Text = "Accelerometer Enabled";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.listInfo);
            this.groupBox3.Location = new System.Drawing.Point(245, 12);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(168, 443);
            this.groupBox3.TabIndex = 3;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Hardware Status";
            // 
            // listInfo
            // 
            this.listInfo.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listInfo.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2});
            this.listInfo.FullRowSelect = true;
            this.listInfo.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.listInfo.Location = new System.Drawing.Point(10, 19);
            this.listInfo.MultiSelect = false;
            this.listInfo.Name = "listInfo";
            this.listInfo.Size = new System.Drawing.Size(149, 415);
            this.listInfo.TabIndex = 3;
            this.listInfo.UseCompatibleStateImageBehavior = false;
            this.listInfo.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "Variable";
            this.columnHeader1.Width = 70;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Value";
            this.columnHeader2.Width = 70;
            // 
            // infoUpdateTimer
            // 
            this.infoUpdateTimer.Interval = 10;
            this.infoUpdateTimer.Tick += new System.EventHandler(this.infoUpdateTimer_Tick);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.listTasks);
            this.groupBox4.Location = new System.Drawing.Point(420, 12);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(170, 443);
            this.groupBox4.TabIndex = 4;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Tasks";
            // 
            // listTasks
            // 
            this.listTasks.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listTasks.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader3,
            this.columnHeader4});
            this.listTasks.FullRowSelect = true;
            this.listTasks.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.listTasks.Location = new System.Drawing.Point(11, 19);
            this.listTasks.MultiSelect = false;
            this.listTasks.Name = "listTasks";
            this.listTasks.Size = new System.Drawing.Size(149, 415);
            this.listTasks.TabIndex = 4;
            this.listTasks.UseCompatibleStateImageBehavior = false;
            this.listTasks.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "Variable";
            this.columnHeader3.Width = 70;
            // 
            // columnHeader4
            // 
            this.columnHeader4.Text = "Value";
            this.columnHeader4.Width = 70;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(10, 16);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(51, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "SysTick: ";
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.cbSlowTick);
            this.groupBox5.Controls.Add(this.lblSysTick);
            this.groupBox5.Controls.Add(this.label3);
            this.groupBox5.Controls.Add(this.btnShowDevice);
            this.groupBox5.Location = new System.Drawing.Point(12, 355);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(227, 100);
            this.groupBox5.TabIndex = 7;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Control";
            // 
            // lblSysTick
            // 
            this.lblSysTick.AutoSize = true;
            this.lblSysTick.Location = new System.Drawing.Point(61, 16);
            this.lblSysTick.Name = "lblSysTick";
            this.lblSysTick.Size = new System.Drawing.Size(13, 13);
            this.lblSysTick.TabIndex = 8;
            this.lblSysTick.Text = "0";
            // 
            // cbSlowTick
            // 
            this.cbSlowTick.AutoSize = true;
            this.cbSlowTick.Checked = true;
            this.cbSlowTick.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbSlowTick.Location = new System.Drawing.Point(132, 16);
            this.cbSlowTick.Name = "cbSlowTick";
            this.cbSlowTick.Size = new System.Drawing.Size(79, 17);
            this.cbSlowTick.TabIndex = 8;
            this.cbSlowTick.Text = "Slow 1:100";
            this.cbSlowTick.UseVisualStyleBackColor = true;
            this.cbSlowTick.CheckedChanged += new System.EventHandler(this.cbSlowTick_CheckedChanged);
            // 
            // tickTimer
            // 
            this.tickTimer.Interval = 1;
            this.tickTimer.Tick += new System.EventHandler(this.tickTimer_Tick);
            // 
            // fmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(602, 467);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "fmMain";
            this.Text = " Zeitgeber Hardware Emulator";
            this.Load += new System.EventHandler(this.fmMain_Load);
            this.Shown += new System.EventHandler(this.fmMain_Shown);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.tbSysFreq)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tbBatteryVoltage)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
            this.groupBox3.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TrackBar tbBatteryVoltage;
        private System.Windows.Forms.CheckBox cbUsbPower;
        private System.Windows.Forms.CheckBox cbBatteryPower;
        private System.Windows.Forms.Button btnShowDevice;
        private System.Windows.Forms.CheckBox cbCharging;
        private System.Windows.Forms.Label lblBatteryVoltage;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TrackBar trackBar1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox checkBox2;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label lblSysFreq;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TrackBar tbSysFreq;
        private System.Windows.Forms.ListView listInfo;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.Timer infoUpdateTimer;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.ListView listTasks;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.ColumnHeader columnHeader4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Label lblSysTick;
        private System.Windows.Forms.CheckBox cbSlowTick;
        private System.Windows.Forms.Timer tickTimer;

    }
}

