﻿namespace SimpleWebServer
{
    partial class Form1
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
            this.label3 = new System.Windows.Forms.Label();
            this.ipAddresses = new System.Windows.Forms.Label();
            this.btnTest = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.btnStop = new System.Windows.Forms.Button();
            this.btnStart = new System.Windows.Forms.Button();
            this.txtContentPath = new System.Windows.Forms.TextBox();
            this.autoStart = new System.Windows.Forms.CheckBox();
            this.nudIP4 = new System.Windows.Forms.NumericUpDown();
            this.nudIP3 = new System.Windows.Forms.NumericUpDown();
            this.nudIP2 = new System.Windows.Forms.NumericUpDown();
            this.nudIP1 = new System.Windows.Forms.NumericUpDown();
            this.nudPort = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.nudIP4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudIP3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudIP2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudIP1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudPort)).BeginInit();
            this.SuspendLayout();
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 55);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(119, 13);
            this.label3.TabIndex = 28;
            this.label3.Text = "Корневая папка (root):";
            // 
            // ipAddresses
            // 
            this.ipAddresses.Location = new System.Drawing.Point(10, 128);
            this.ipAddresses.Name = "ipAddresses";
            this.ipAddresses.Size = new System.Drawing.Size(265, 19);
            this.ipAddresses.TabIndex = 26;
            this.ipAddresses.Text = "Локальный IP: ";
            this.ipAddresses.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // btnTest
            // 
            this.btnTest.Enabled = false;
            this.btnTest.Location = new System.Drawing.Point(107, 99);
            this.btnTest.Name = "btnTest";
            this.btnTest.Size = new System.Drawing.Size(75, 23);
            this.btnTest.TabIndex = 24;
            this.btnTest.Text = "Тест";
            this.btnTest.UseVisualStyleBackColor = true;
            this.btnTest.Click += new System.EventHandler(this.btnTest_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(217, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 13);
            this.label2.TabIndex = 23;
            this.label2.Text = "Порт:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 13);
            this.label1.TabIndex = 22;
            this.label1.Text = "IP адрес:";
            // 
            // btnStop
            // 
            this.btnStop.Enabled = false;
            this.btnStop.Location = new System.Drawing.Point(188, 99);
            this.btnStop.Name = "btnStop";
            this.btnStop.Size = new System.Drawing.Size(75, 23);
            this.btnStop.TabIndex = 16;
            this.btnStop.Text = "Стоп";
            this.btnStop.UseVisualStyleBackColor = true;
            this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
            // 
            // btnStart
            // 
            this.btnStart.Location = new System.Drawing.Point(26, 99);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(75, 23);
            this.btnStart.TabIndex = 15;
            this.btnStart.Text = "Старт";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // txtContentPath
            // 
            this.txtContentPath.DataBindings.Add(new System.Windows.Forms.Binding("Text", global::SimpleWebServer.Properties.Settings.Default, "path", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.txtContentPath.Location = new System.Drawing.Point(15, 71);
            this.txtContentPath.Name = "txtContentPath";
            this.txtContentPath.Size = new System.Drawing.Size(262, 20);
            this.txtContentPath.TabIndex = 27;
            this.txtContentPath.Text = global::SimpleWebServer.Properties.Settings.Default.path;
            // 
            // autoStart
            // 
            this.autoStart.AutoSize = true;
            this.autoStart.Checked = global::SimpleWebServer.Properties.Settings.Default.start;
            this.autoStart.DataBindings.Add(new System.Windows.Forms.Binding("Checked", global::SimpleWebServer.Properties.Settings.Default, "start", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.autoStart.Location = new System.Drawing.Point(21, 149);
            this.autoStart.Name = "autoStart";
            this.autoStart.Size = new System.Drawing.Size(234, 17);
            this.autoStart.TabIndex = 25;
            this.autoStart.Text = "Запуск сервера при запуске программы";
            this.autoStart.UseVisualStyleBackColor = true;
            // 
            // nudIP4
            // 
            this.nudIP4.DataBindings.Add(new System.Windows.Forms.Binding("Value", global::SimpleWebServer.Properties.Settings.Default, "ip4", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.nudIP4.Location = new System.Drawing.Point(169, 26);
            this.nudIP4.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nudIP4.Name = "nudIP4";
            this.nudIP4.Size = new System.Drawing.Size(45, 20);
            this.nudIP4.TabIndex = 21;
            this.nudIP4.Value = global::SimpleWebServer.Properties.Settings.Default.ip4;
            // 
            // nudIP3
            // 
            this.nudIP3.DataBindings.Add(new System.Windows.Forms.Binding("Value", global::SimpleWebServer.Properties.Settings.Default, "ip3", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.nudIP3.Location = new System.Drawing.Point(118, 26);
            this.nudIP3.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nudIP3.Name = "nudIP3";
            this.nudIP3.Size = new System.Drawing.Size(45, 20);
            this.nudIP3.TabIndex = 20;
            this.nudIP3.Value = global::SimpleWebServer.Properties.Settings.Default.ip3;
            // 
            // nudIP2
            // 
            this.nudIP2.DataBindings.Add(new System.Windows.Forms.Binding("Value", global::SimpleWebServer.Properties.Settings.Default, "ip2", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.nudIP2.Location = new System.Drawing.Point(66, 26);
            this.nudIP2.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nudIP2.Name = "nudIP2";
            this.nudIP2.Size = new System.Drawing.Size(45, 20);
            this.nudIP2.TabIndex = 19;
            this.nudIP2.Value = global::SimpleWebServer.Properties.Settings.Default.ip2;
            // 
            // nudIP1
            // 
            this.nudIP1.DataBindings.Add(new System.Windows.Forms.Binding("Value", global::SimpleWebServer.Properties.Settings.Default, "ip1", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.nudIP1.Location = new System.Drawing.Point(15, 26);
            this.nudIP1.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nudIP1.Name = "nudIP1";
            this.nudIP1.Size = new System.Drawing.Size(45, 20);
            this.nudIP1.TabIndex = 18;
            this.nudIP1.Value = global::SimpleWebServer.Properties.Settings.Default.ip1;
            // 
            // nudPort
            // 
            this.nudPort.DataBindings.Add(new System.Windows.Forms.Binding("Value", global::SimpleWebServer.Properties.Settings.Default, "port", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.nudPort.Location = new System.Drawing.Point(220, 26);
            this.nudPort.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.nudPort.Name = "nudPort";
            this.nudPort.Size = new System.Drawing.Size(57, 20);
            this.nudPort.TabIndex = 17;
            this.nudPort.Value = global::SimpleWebServer.Properties.Settings.Default.port;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(292, 177);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.txtContentPath);
            this.Controls.Add(this.ipAddresses);
            this.Controls.Add(this.autoStart);
            this.Controls.Add(this.btnTest);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.nudIP4);
            this.Controls.Add(this.nudIP3);
            this.Controls.Add(this.nudIP2);
            this.Controls.Add(this.nudIP1);
            this.Controls.Add(this.nudPort);
            this.Controls.Add(this.btnStop);
            this.Controls.Add(this.btnStart);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "WebServer";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Shown += new System.EventHandler(this.Form1_Shown);
            this.SizeChanged += new System.EventHandler(this.Form1_SizeChanged);
            ((System.ComponentModel.ISupportInitialize)(this.nudIP4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudIP3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudIP2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudIP1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudPort)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtContentPath;
        private System.Windows.Forms.Label ipAddresses;
        private System.Windows.Forms.CheckBox autoStart;
        private System.Windows.Forms.Button btnTest;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown nudIP4;
        private System.Windows.Forms.NumericUpDown nudIP3;
        private System.Windows.Forms.NumericUpDown nudIP2;
        private System.Windows.Forms.NumericUpDown nudIP1;
        private System.Windows.Forms.NumericUpDown nudPort;
        private System.Windows.Forms.Button btnStop;
        private System.Windows.Forms.Button btnStart;
    }
}

