using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.Reflection;

using Zeitgeber;
namespace ZeitgeberEmulator
{
    public partial class fmMain : Form
    {
        //public Dictionary<string, object> info;
        private static int startTick = 0;
        public static UInt16 fastTick = 0;
        public static UInt16 slowTick = 0;

        public fmMain()
        {
            InitializeComponent();

            startTick = Environment.TickCount;

            //info = new Dictionary<string, object>();
        }

        private void fmMain_Shown(object sender, EventArgs e)
        {
            Program.fmDevice.Show();
        }

        private void btnShowDevice_Click(object sender, EventArgs e)
        {
            Program.fmDevice.Show();
        }

        private void cbUsbPower_CheckedChanged(object sender, EventArgs e)
        {
            cbCharging.Enabled = cbUsbPower.Checked;
            if (cbCharging.Enabled == false)
            {
                cbCharging.Checked = false;
            }
        }

        private void cbBatteryPower_CheckedChanged(object sender, EventArgs e)
        {
            tbBatteryVoltage.Enabled = cbBatteryPower.Checked;
        }

        private void tbBatteryVoltage_Scroll(object sender, EventArgs e)
        {
            lblBatteryVoltage.Text = String.Format("{0:f2} V", tbBatteryVoltage.Value / 1000.0); 
        }

        private void tbSysFreq_Scroll(object sender, EventArgs e)
        {
            lblSysFreq.Text = String.Format("{0:f0} MHz", tbSysFreq.Value / 1000.0);
        }

        private void fmMain_Load(object sender, EventArgs e)
        {
            listInfo.Items.Clear();
            listInfo.Columns[0].Width = listInfo.Width / 2 - 1;
            listInfo.Columns[1].Width = listInfo.Width / 2 - 2;

            //UpdateInfo();

            PopulateInfo();


            infoUpdateTimer.Enabled = true;
            tickTimer.Enabled = true;
        }

        private Dictionary<string, object> StructToDictionary(object obj, Type typ)
        {
            var dict = new Dictionary<string, object>();

            //FieldInfo[] fi = typ.GetFields(BindingFlags.Public | BindingFlags.Instance | BindingFlags.NonPublic);
            FieldInfo[] fi = typ.GetFields(BindingFlags.Public | BindingFlags.Instance);
            foreach (FieldInfo info in fi)
                dict[info.Name] = info.GetValue(obj);

            return dict;
        }

        private void PopulateInfo()
        {
            // Hardware Status Info
            {
                HardwareStatus status = new HardwareStatus();
                var dict = StructToDictionary(status, typeof(HardwareStatus));
                foreach (var info in dict)
                {
                    ListViewItem item = listInfo.Items.Add(info.Key);
                    item.SubItems.Add(info.Value.ToString());
                }
            }


            // Tasks
            Task[] tasks = dll.GetSchedulerTasks();
            foreach (Task task in tasks)
            {
                var dict = StructToDictionary(task, typeof(Task));

                var group = listTasks.Groups.Add(task.name, task.name);
                foreach (var info in dict)
                {
                    var item = listTasks.Items.Add(info.Key);
                    item.Group = group;
                    item.SubItems.Add(info.Value.ToString());
                }
            }
        }

        public void UpdateInfo()
        {
            // Hardware Status Info
            {
                //listInfo.BeginUpdate();
                HardwareStatus status = dll.GetHardwareStatus();
                var dict = StructToDictionary(status, typeof(HardwareStatus));

                int i = 0;
                foreach (var info in dict)
                {
                    var item = listInfo.Items[i++];
                    string newValue = info.Value.ToString();
                    if (item.SubItems[1].Text != newValue)
                        item.SubItems[1].Text = newValue;
                }
                //listInfo.EndUpdate();
            }

            // Tasks
            {
                //listTasks.BeginUpdate();
                Task[] tasks = dll.GetSchedulerTasks();
                int i = 0;
                foreach (Task task in tasks)
                {
                    var dict = StructToDictionary(task, typeof(Task));
                    foreach (var info in dict)
                    {
                        var item = listTasks.Items[i++];
                        string newValue = info.Value.ToString();
                        if (item.SubItems[1].Text != newValue)
                            item.SubItems[1].Text = newValue;
                    }
                }
                //listTasks.EndUpdate();
            }

        }

        private void infoUpdateTimer_Tick(object sender, EventArgs e)
        {
            UpdateInfo();
        }

        private void button1_Click(object sender, EventArgs e)
        {

        }

        private void cbSlowTick_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void tickTimer_Tick(object sender, EventArgs e)
        {
            //UInt16 tick = (cbSlowTick.Checked) ? (UInt16)(slowTick+fastTick) : fastTick;
            UInt16 tick = (UInt16)(slowTick + fastTick);

            if (!cbSlowTick.Checked)
                fastTick = (UInt16)(Environment.TickCount - startTick);
            else
                slowTick = (UInt16)((Environment.TickCount - startTick) / 100);

            lblSysTick.Text = String.Format("{0} ms", tick);

            dll.SetSystick((UInt16)tick);
            dll.Process();
        }
    }
}
