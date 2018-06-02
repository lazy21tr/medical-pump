namespace pcapp
{
    partial class AppMainForm
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
            this.RS232 = new System.IO.Ports.SerialPort(this.components);
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.mainBoardToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.readTemperatureToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.readSensorsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.readBalancer1ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.readBalancer2ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.readEncoderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.readRFID1ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.readRFID2ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.readFWVersionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.operationsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.runPeristalticPumpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.runStepperMotorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.resetEncoderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.fillupLargeBagToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.fillupSmallBagToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.resetTareBalancer1ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.resetTareBalancer2ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.resetBalancer1ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.resetBalancer2ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.initRFID1ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.initRFID2ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.calibrationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.calibrateBalancer1ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.calibrateBalancer2ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.lblResponse = new System.Windows.Forms.Label();
            this.button6 = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.button8 = new System.Windows.Forms.Button();
            this.button9 = new System.Windows.Forms.Button();
            this.button10 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.lblFillup = new System.Windows.Forms.Label();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // RS232
            // 
            this.RS232.BaudRate = 19200;
            this.RS232.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.RS232_DataReceived);
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mainBoardToolStripMenuItem,
            this.operationsToolStripMenuItem,
            this.calibrationToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(493, 24);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // mainBoardToolStripMenuItem
            // 
            this.mainBoardToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.readTemperatureToolStripMenuItem,
            this.readSensorsToolStripMenuItem,
            this.readBalancer1ToolStripMenuItem,
            this.readBalancer2ToolStripMenuItem,
            this.readEncoderToolStripMenuItem,
            this.readRFID1ToolStripMenuItem,
            this.readRFID2ToolStripMenuItem,
            this.readFWVersionToolStripMenuItem});
            this.mainBoardToolStripMenuItem.Name = "mainBoardToolStripMenuItem";
            this.mainBoardToolStripMenuItem.Size = new System.Drawing.Size(61, 20);
            this.mainBoardToolStripMenuItem.Text = "Get Info";
            // 
            // readTemperatureToolStripMenuItem
            // 
            this.readTemperatureToolStripMenuItem.Name = "readTemperatureToolStripMenuItem";
            this.readTemperatureToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.readTemperatureToolStripMenuItem.Text = "Read Temperature";
            this.readTemperatureToolStripMenuItem.Click += new System.EventHandler(this.sendCommandNoParameter);
            // 
            // readSensorsToolStripMenuItem
            // 
            this.readSensorsToolStripMenuItem.Name = "readSensorsToolStripMenuItem";
            this.readSensorsToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.readSensorsToolStripMenuItem.Text = "Read Sensors";
            this.readSensorsToolStripMenuItem.Click += new System.EventHandler(this.sendCommandNoParameter);
            // 
            // readBalancer1ToolStripMenuItem
            // 
            this.readBalancer1ToolStripMenuItem.Name = "readBalancer1ToolStripMenuItem";
            this.readBalancer1ToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.readBalancer1ToolStripMenuItem.Text = "Read Balancer1";
            this.readBalancer1ToolStripMenuItem.Click += new System.EventHandler(this.sendCommandNoParameter);
            // 
            // readBalancer2ToolStripMenuItem
            // 
            this.readBalancer2ToolStripMenuItem.Name = "readBalancer2ToolStripMenuItem";
            this.readBalancer2ToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.readBalancer2ToolStripMenuItem.Text = "Read Balancer2";
            this.readBalancer2ToolStripMenuItem.Click += new System.EventHandler(this.sendCommandNoParameter);
            // 
            // readEncoderToolStripMenuItem
            // 
            this.readEncoderToolStripMenuItem.Name = "readEncoderToolStripMenuItem";
            this.readEncoderToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.readEncoderToolStripMenuItem.Text = "Read Encoder";
            this.readEncoderToolStripMenuItem.Click += new System.EventHandler(this.sendCommandNoParameter);
            // 
            // readRFID1ToolStripMenuItem
            // 
            this.readRFID1ToolStripMenuItem.Name = "readRFID1ToolStripMenuItem";
            this.readRFID1ToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.readRFID1ToolStripMenuItem.Text = "Read RFID1";
            this.readRFID1ToolStripMenuItem.Click += new System.EventHandler(this.sendCommandNoParameter);
            // 
            // readRFID2ToolStripMenuItem
            // 
            this.readRFID2ToolStripMenuItem.Name = "readRFID2ToolStripMenuItem";
            this.readRFID2ToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.readRFID2ToolStripMenuItem.Text = "Read RFID2";
            this.readRFID2ToolStripMenuItem.Click += new System.EventHandler(this.sendCommandNoParameter);
            // 
            // readFWVersionToolStripMenuItem
            // 
            this.readFWVersionToolStripMenuItem.Name = "readFWVersionToolStripMenuItem";
            this.readFWVersionToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.readFWVersionToolStripMenuItem.Text = "Read FW Version";
            this.readFWVersionToolStripMenuItem.Click += new System.EventHandler(this.sendCommandNoParameter);
            // 
            // operationsToolStripMenuItem
            // 
            this.operationsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.runPeristalticPumpToolStripMenuItem,
            this.runStepperMotorToolStripMenuItem,
            this.resetEncoderToolStripMenuItem,
            this.fillupLargeBagToolStripMenuItem,
            this.fillupSmallBagToolStripMenuItem,
            this.resetTareBalancer1ToolStripMenuItem,
            this.resetTareBalancer2ToolStripMenuItem,
            this.resetBalancer1ToolStripMenuItem,
            this.resetBalancer2ToolStripMenuItem,
            this.initRFID1ToolStripMenuItem,
            this.initRFID2ToolStripMenuItem});
            this.operationsToolStripMenuItem.Name = "operationsToolStripMenuItem";
            this.operationsToolStripMenuItem.Size = new System.Drawing.Size(77, 20);
            this.operationsToolStripMenuItem.Text = "Operations";
            // 
            // runPeristalticPumpToolStripMenuItem
            // 
            this.runPeristalticPumpToolStripMenuItem.Name = "runPeristalticPumpToolStripMenuItem";
            this.runPeristalticPumpToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.runPeristalticPumpToolStripMenuItem.Text = "Run Peristaltic Pump";
            this.runPeristalticPumpToolStripMenuItem.Click += new System.EventHandler(this.sendCommandSingleParameter);
            // 
            // runStepperMotorToolStripMenuItem
            // 
            this.runStepperMotorToolStripMenuItem.Name = "runStepperMotorToolStripMenuItem";
            this.runStepperMotorToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.runStepperMotorToolStripMenuItem.Text = "Run Stepper Motor";
            this.runStepperMotorToolStripMenuItem.Click += new System.EventHandler(this.sendCommandDualParameter);
            // 
            // resetEncoderToolStripMenuItem
            // 
            this.resetEncoderToolStripMenuItem.Name = "resetEncoderToolStripMenuItem";
            this.resetEncoderToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.resetEncoderToolStripMenuItem.Text = "Reset Encoder";
            this.resetEncoderToolStripMenuItem.Click += new System.EventHandler(this.sendCommandNoParameter);
            // 
            // fillupLargeBagToolStripMenuItem
            // 
            this.fillupLargeBagToolStripMenuItem.Name = "fillupLargeBagToolStripMenuItem";
            this.fillupLargeBagToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.fillupLargeBagToolStripMenuItem.Text = "Fillup Large Bag";
            this.fillupLargeBagToolStripMenuItem.Click += new System.EventHandler(this.sendCommandSingleParameter);
            // 
            // fillupSmallBagToolStripMenuItem
            // 
            this.fillupSmallBagToolStripMenuItem.Name = "fillupSmallBagToolStripMenuItem";
            this.fillupSmallBagToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.fillupSmallBagToolStripMenuItem.Text = "Fillup Small Bag";
            this.fillupSmallBagToolStripMenuItem.Click += new System.EventHandler(this.sendCommandSingleParameter);
            // 
            // resetTareBalancer1ToolStripMenuItem
            // 
            this.resetTareBalancer1ToolStripMenuItem.Name = "resetTareBalancer1ToolStripMenuItem";
            this.resetTareBalancer1ToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.resetTareBalancer1ToolStripMenuItem.Text = "Reset Tare Balancer1";
            this.resetTareBalancer1ToolStripMenuItem.Click += new System.EventHandler(this.sendCommandNoParameter);
            // 
            // resetTareBalancer2ToolStripMenuItem
            // 
            this.resetTareBalancer2ToolStripMenuItem.Name = "resetTareBalancer2ToolStripMenuItem";
            this.resetTareBalancer2ToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.resetTareBalancer2ToolStripMenuItem.Text = "Reset Tare Balancer2";
            this.resetTareBalancer2ToolStripMenuItem.Click += new System.EventHandler(this.sendCommandNoParameter);
            // 
            // resetBalancer1ToolStripMenuItem
            // 
            this.resetBalancer1ToolStripMenuItem.Name = "resetBalancer1ToolStripMenuItem";
            this.resetBalancer1ToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.resetBalancer1ToolStripMenuItem.Text = "Reset Balancer1";
            this.resetBalancer1ToolStripMenuItem.Click += new System.EventHandler(this.sendCommandNoParameter);
            // 
            // resetBalancer2ToolStripMenuItem
            // 
            this.resetBalancer2ToolStripMenuItem.Name = "resetBalancer2ToolStripMenuItem";
            this.resetBalancer2ToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.resetBalancer2ToolStripMenuItem.Text = "Reset Balancer2";
            this.resetBalancer2ToolStripMenuItem.Click += new System.EventHandler(this.sendCommandNoParameter);
            // 
            // initRFID1ToolStripMenuItem
            // 
            this.initRFID1ToolStripMenuItem.Name = "initRFID1ToolStripMenuItem";
            this.initRFID1ToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.initRFID1ToolStripMenuItem.Text = "Init RFID1";
            this.initRFID1ToolStripMenuItem.Click += new System.EventHandler(this.sendCommandNoParameter);
            // 
            // initRFID2ToolStripMenuItem
            // 
            this.initRFID2ToolStripMenuItem.Name = "initRFID2ToolStripMenuItem";
            this.initRFID2ToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.initRFID2ToolStripMenuItem.Text = "Init RFID2";
            this.initRFID2ToolStripMenuItem.Click += new System.EventHandler(this.sendCommandNoParameter);
            // 
            // calibrationToolStripMenuItem
            // 
            this.calibrationToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.calibrateBalancer1ToolStripMenuItem,
            this.calibrateBalancer2ToolStripMenuItem});
            this.calibrationToolStripMenuItem.Name = "calibrationToolStripMenuItem";
            this.calibrationToolStripMenuItem.Size = new System.Drawing.Size(77, 20);
            this.calibrationToolStripMenuItem.Text = "Calibration";
            // 
            // calibrateBalancer1ToolStripMenuItem
            // 
            this.calibrateBalancer1ToolStripMenuItem.Name = "calibrateBalancer1ToolStripMenuItem";
            this.calibrateBalancer1ToolStripMenuItem.Size = new System.Drawing.Size(178, 22);
            this.calibrateBalancer1ToolStripMenuItem.Text = "Calibrate Balancer 1";
            this.calibrateBalancer1ToolStripMenuItem.Click += new System.EventHandler(this.sendCommandNoParameter);
            // 
            // calibrateBalancer2ToolStripMenuItem
            // 
            this.calibrateBalancer2ToolStripMenuItem.Name = "calibrateBalancer2ToolStripMenuItem";
            this.calibrateBalancer2ToolStripMenuItem.Size = new System.Drawing.Size(178, 22);
            this.calibrateBalancer2ToolStripMenuItem.Text = "Calibrate Balancer 2";
            this.calibrateBalancer2ToolStripMenuItem.Click += new System.EventHandler(this.sendCommandNoParameter);
            // 
            // lblResponse
            // 
            this.lblResponse.AutoSize = true;
            this.lblResponse.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.lblResponse.Location = new System.Drawing.Point(12, 87);
            this.lblResponse.Name = "lblResponse";
            this.lblResponse.Size = new System.Drawing.Size(201, 20);
            this.lblResponse.TabIndex = 3;
            this.lblResponse.Text = "Response appears here";
            // 
            // button6
            // 
            this.button6.BackColor = System.Drawing.Color.Red;
            this.button6.Enabled = false;
            this.button6.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.button6.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.button6.Location = new System.Drawing.Point(205, 241);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(38, 41);
            this.button6.TabIndex = 21;
            this.button6.Text = "6";
            this.button6.UseVisualStyleBackColor = false;
            // 
            // button7
            // 
            this.button7.BackColor = System.Drawing.Color.Red;
            this.button7.Enabled = false;
            this.button7.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.button7.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.button7.Location = new System.Drawing.Point(158, 241);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(38, 41);
            this.button7.TabIndex = 20;
            this.button7.Text = "7";
            this.button7.UseVisualStyleBackColor = false;
            // 
            // button8
            // 
            this.button8.BackColor = System.Drawing.Color.Red;
            this.button8.Enabled = false;
            this.button8.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.button8.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.button8.Location = new System.Drawing.Point(112, 241);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(38, 41);
            this.button8.TabIndex = 19;
            this.button8.Text = "8";
            this.button8.UseVisualStyleBackColor = false;
            // 
            // button9
            // 
            this.button9.BackColor = System.Drawing.Color.Red;
            this.button9.Enabled = false;
            this.button9.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.button9.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.button9.Location = new System.Drawing.Point(65, 241);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(38, 41);
            this.button9.TabIndex = 18;
            this.button9.Text = "9";
            this.button9.UseVisualStyleBackColor = false;
            // 
            // button10
            // 
            this.button10.BackColor = System.Drawing.Color.Red;
            this.button10.Enabled = false;
            this.button10.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.button10.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.button10.Location = new System.Drawing.Point(19, 241);
            this.button10.Name = "button10";
            this.button10.Size = new System.Drawing.Size(38, 41);
            this.button10.TabIndex = 17;
            this.button10.Text = "10";
            this.button10.UseVisualStyleBackColor = false;
            // 
            // button5
            // 
            this.button5.BackColor = System.Drawing.Color.Red;
            this.button5.Enabled = false;
            this.button5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.button5.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.button5.Location = new System.Drawing.Point(251, 241);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(38, 41);
            this.button5.TabIndex = 16;
            this.button5.Text = "5";
            this.button5.UseVisualStyleBackColor = false;
            // 
            // button4
            // 
            this.button4.BackColor = System.Drawing.Color.Red;
            this.button4.Enabled = false;
            this.button4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.button4.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.button4.Location = new System.Drawing.Point(298, 241);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(38, 41);
            this.button4.TabIndex = 15;
            this.button4.Text = "4";
            this.button4.UseVisualStyleBackColor = false;
            // 
            // button3
            // 
            this.button3.BackColor = System.Drawing.Color.Red;
            this.button3.Enabled = false;
            this.button3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.button3.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.button3.Location = new System.Drawing.Point(344, 241);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(38, 41);
            this.button3.TabIndex = 14;
            this.button3.Text = "3";
            this.button3.UseVisualStyleBackColor = false;
            // 
            // button2
            // 
            this.button2.BackColor = System.Drawing.Color.Red;
            this.button2.Enabled = false;
            this.button2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.button2.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.button2.Location = new System.Drawing.Point(391, 241);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(38, 41);
            this.button2.TabIndex = 13;
            this.button2.Text = "2";
            this.button2.UseVisualStyleBackColor = false;
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.Color.Red;
            this.button1.Enabled = false;
            this.button1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.button1.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.button1.Location = new System.Drawing.Point(437, 241);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(38, 41);
            this.button1.TabIndex = 12;
            this.button1.Text = "1";
            this.button1.UseVisualStyleBackColor = false;
            // 
            // lblFillup
            // 
            this.lblFillup.AutoSize = true;
            this.lblFillup.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.lblFillup.Location = new System.Drawing.Point(15, 116);
            this.lblFillup.Name = "lblFillup";
            this.lblFillup.Size = new System.Drawing.Size(282, 20);
            this.lblFillup.TabIndex = 22;
            this.lblFillup.Text = "Waiting for the bag to get filled up";
            // 
            // AppMainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(493, 323);
            this.Controls.Add(this.lblFillup);
            this.Controls.Add(this.button6);
            this.Controls.Add(this.button7);
            this.Controls.Add(this.button8);
            this.Controls.Add(this.button9);
            this.Controls.Add(this.button10);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.lblResponse);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "AppMainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "AppMainForm";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem mainBoardToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem readTemperatureToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem readSensorsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem readBalancer1ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem readBalancer2ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem readEncoderToolStripMenuItem;
        private System.Windows.Forms.Label lblResponse;
        private System.Windows.Forms.ToolStripMenuItem operationsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem fillupLargeBagToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem readRFID1ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem readRFID2ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem readFWVersionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem fillupSmallBagToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem resetBalancer1ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem resetBalancer2ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem runPeristalticPumpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem runStepperMotorToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem resetEncoderToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem resetTareBalancer1ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem resetTareBalancer2ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem calibrationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem calibrateBalancer1ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem calibrateBalancer2ToolStripMenuItem;
        public System.IO.Ports.SerialPort RS232;
        private System.Windows.Forms.ToolStripMenuItem initRFID1ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem initRFID2ToolStripMenuItem;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.Button button10;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label lblFillup;
    }
}

