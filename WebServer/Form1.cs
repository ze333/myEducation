using System;
using System.Globalization;
using System.Windows.Forms;
using System.Net;
using System.Text.RegularExpressions;
using System.Threading;

namespace SimpleWebServer
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        readonly Server _server = new Server();

        private void btnStart_Click(object sender, EventArgs e)
        {
            IPAddress ipAddress = IPAddress.Parse(nudIP1.Value.ToString(CultureInfo.InvariantCulture) + "." +
                nudIP2.Value.ToString(CultureInfo.InvariantCulture) + "." +
                nudIP3.Value.ToString(CultureInfo.InvariantCulture) + "." +
                nudIP4.Value.ToString(CultureInfo.InvariantCulture));
            if (_server.Start(ipAddress, Convert.ToInt32(nudPort.Value), 100, txtContentPath.Text))
            {
                btnStart.Enabled = false;
                btnStop.Enabled = true;
                btnTest.Enabled = true;
            }
            else
                MessageBox.Show(this, @"Невозможно звпустить север. Быть может порт " +
                    nudPort.Value.ToString(CultureInfo.InvariantCulture) +
                                                            @" занят другой программой.", @"Error",
                                                                        MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            _server.Stop();
            btnStart.Enabled = true;
            btnStop.Enabled = false;
            btnTest.Enabled = false;
        }

        private bool _startedUp;
        private void Form1_Shown(object sender, EventArgs e)
        {
            if (_startedUp) return;
            _startedUp = true;

            if (Properties.Settings.Default.start)
            {
                WindowState = FormWindowState.Minimized;
                Hide();
                btnStart_Click(null, null);
            }

            ipAddresses.Text = null;
            ThreadPool.QueueUserWorkItem(arg =>
            {
                try
                {
                    string externalIp = null;
                    try
                    {
                        externalIp = (new WebClient()).DownloadString("http://checkip.dyndns.org/");
                        externalIp = (new Regex(@"\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}")).Matches(externalIp)[0].ToString();
                    }
                    catch { }
                    Invoke((Action)(() => { ipAddresses.Text = @"Внутренний IP: " +
                                         Dns.GetHostByName(Dns.GetHostName()).AddressList[0] +
                                             (externalIp == null ? "" : ", Внешний IP: " + externalIp); }));
                }catch{}
            });
        }

        private void btnTest_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("explorer.exe", "http://" + nudIP1.Value.ToString(CultureInfo.InvariantCulture) + "." +
                nudIP2.Value.ToString(CultureInfo.InvariantCulture) + "." +
                nudIP3.Value.ToString(CultureInfo.InvariantCulture) + "." +
                nudIP4.Value.ToString(CultureInfo.InvariantCulture) + 
                (nudPort.Value == 80 ? "" : ":" + nudPort.Value.ToString(CultureInfo.InvariantCulture)));
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            btnStop.PerformClick();
            Properties.Settings.Default.Save();
        }

        private void trayIcon_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            Show();
            trayIcon.Visible = false;
            WindowState = FormWindowState.Normal;
        }

        private void Form1_SizeChanged(object sender, EventArgs e)
        {
            if (WindowState == FormWindowState.Minimized)
            {
                trayIcon.Visible = true;
                Hide();
            }
        }
    }
}
