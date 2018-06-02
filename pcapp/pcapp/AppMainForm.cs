using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace pcapp
{
    public partial class AppMainForm : Form
    {
        private static AppMainForm instance = null;
        private CalibrationWizard frmCalibrationWizard = null;
        public AppMainForm()
        {
            InitializeComponent();
            prepareUserEnvironment();
            instance = this;
        }

        public static AppMainForm getInstance()
        {
            return instance;
        }

        UserDialogForm frmUserDialog = new UserDialogForm();
        private void prepareUserEnvironment()
        {
            try
            {
                if (RS232.IsOpen)
                    RS232.Close();
                RS232.NewLine = "<EOM>";
                RS232.BaudRate = 19200;
                RS232.Open();
            }
            catch (Exception)
            {
                MessageBox.Show("Seri Port Açılamadı", "Hata", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }

        private void RS232_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            try
            {
                string message = RS232.ReadLine().Substring(5);
                this.Invoke(new MethodInvoker(delegate()
                {
                    lblResponse.Text = message;

                    if (message.StartsWith("Sens: "))
                        evaluateSensors(message.Substring(6));
                    if (message.StartsWith("Filled: "))
                        lblFillup.Text = "The Bag Filled Up!";

                    if (frmCalibrationWizard != null)
                    {
                        frmCalibrationWizard.processMessage(message);
                    }
                }));
            }
            catch (Exception)
            {
                MessageBox.Show("Seri Port Okunamadı", "Hata", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }

        private void evaluateSensors(string sensData) {
            string hex = sensData;
            Int32 dec = Convert.ToInt32(hex, 16);
            string bin = Convert.ToString(dec, 2).PadLeft(10, '0');

            if (bin[0] == '1')
                button10.BackColor = Color.Green;
            else
                button10.BackColor = Color.Red;
            if (bin[1] == '1')
                button9.BackColor = Color.Green;
            else
                button9.BackColor = Color.Red;
            if (bin[2] == '1')
                button8.BackColor = Color.Green;
            else
                button8.BackColor = Color.Red;
            if (bin[3] == '1')
                button7.BackColor = Color.Green;
            else
                button7.BackColor = Color.Red;
            if (bin[4] == '1')
                button6.BackColor = Color.Green;
            else
                button6.BackColor = Color.Red;
            if (bin[5] == '1')
                button5.BackColor = Color.Green;
            else
                button5.BackColor = Color.Red;
            if (bin[6] == '1')
                button4.BackColor = Color.Green;
            else
                button4.BackColor = Color.Red;
            if (bin[7] == '1')
                button3.BackColor = Color.Green;
            else
                button3.BackColor = Color.Red;
            if (bin[8] == '1')
                button2.BackColor = Color.Green;
            else
                button2.BackColor = Color.Red;
            if (bin[9] == '1')
                button1.BackColor = Color.Green;
            else
                button1.BackColor = Color.Red;
        }

        private void sendCommandNoParameter(object sender, EventArgs e)
        {
            if (sender is ToolStripMenuItem)
            {
                ToolStripMenuItem menu = (ToolStripMenuItem)sender;
                switch (menu.Name) {
                    case "readTemperatureToolStripMenuItem":
                        RS232.WriteLine("$00RFA---****----****----****----****");
                        break;
                    case "readSensorsToolStripMenuItem":
                        RS232.WriteLine("$00RFB---****----****----****----****");
                        break;
                    case "readBalancer1ToolStripMenuItem":
                        RS232.WriteLine("$00RFC---****----****----****----****");
                        break;
                    case "readBalancer2ToolStripMenuItem":
                        RS232.WriteLine("$00RFD---****----****----****----****");
                        break;
                    case "readEncoderToolStripMenuItem":
                        RS232.WriteLine("$00RFE---****----****----****----****");
                        break;
                    case "readRFID1ToolStripMenuItem":
                        RS232.WriteLine("$00RFF99C****----****----****----****");
                        break;
                    case "readRFID2ToolStripMenuItem":
                        RS232.WriteLine("$00RFG99C****----****----****----****");
                        break;
                    case "initRFID1ToolStripMenuItem":
                        RS232.WriteLine("$00RFF1--****----****----****----****");
                        break;
                    case "initRFID2ToolStripMenuItem":
                        RS232.WriteLine("$00RFG1--****----****----****----****");
                        break;
                    case "readFWVersionToolStripMenuItem":
                        RS232.WriteLine("$00RFH---****----****----****----****");
                        break;
                    case "resetEncoderToolStripMenuItem":
                        RS232.WriteLine("$00RFM---****----****----****----****");
                        break;
                    case "resetTareBalancer1ToolStripMenuItem":
                        RS232.WriteLine("$00RFN---****----****----****----****");
                        break;
                    case "resetTareBalancer2ToolStripMenuItem":
                        RS232.WriteLine("$00RFO---****----****----****----****");
                        break;
                    case "calibrateBalancer1ToolStripMenuItem":
                        frmCalibrationWizard = new CalibrationWizard(1);
                        frmCalibrationWizard.Show();
                        break;
                    case "calibrateBalancer2ToolStripMenuItem":
                        frmCalibrationWizard = new CalibrationWizard(2);
                        frmCalibrationWizard.Show();
                        break;
                    case "resetBalancer1ToolStripMenuItem":
                        RS232.WriteLine("$00RFV---****----****----****----****");
                        break;
                    case "resetBalancer2ToolStripMenuItem":
                        RS232.WriteLine("$00RFW---****----****----****----****");
                        break;
                }
            }
        }

        private void sendCommandSingleParameter(object sender, EventArgs e)
        {
            if (sender is ToolStripMenuItem)
            {
                ToolStripMenuItem menu = (ToolStripMenuItem)sender;
                switch (menu.Name)
                {
                    case "runPeristalticPumpToolStripMenuItem":
                        frmUserDialog.setDialogBoxParameters("Enter speed between [-832,+832]", false, "#000", null);
                        break;
                    case "fillupLargeBagToolStripMenuItem":
                        frmUserDialog.setDialogBoxParameters("Enter weight between [1,3000]g", false, "0000", null);
                        break;
                    case "fillupSmallBagToolStripMenuItem":
                        frmUserDialog.setDialogBoxParameters("Enter weight between [1,3000]g", false, "0000", null);
                        break;
                }
                frmUserDialog.ShowDialog();
                if (frmUserDialog.DialogResult == System.Windows.Forms.DialogResult.OK)
                {
                    string userInput = null;

                    switch (menu.Name)
                    {
                        case "runPeristalticPumpToolStripMenuItem":
                            userInput = "$00RFI" + frmUserDialog.getUserInput1();
                            break;
                        case "fillupLargeBagToolStripMenuItem":
                            userInput = "$00RFK" + frmUserDialog.getUserInput1();
                            lblFillup.Text = "Waiting for the bag to get filled up";
                            break;
                        case "fillupSmallBagToolStripMenuItem":
                            userInput = "$00RFL" + frmUserDialog.getUserInput1();
                            break;
                    }

                    if (userInput != null)
                    {
                        userInput = userInput.PadRight(37, '*');
                        RS232.WriteLine(userInput);
                    }
                }
            }
        }

        private void sendCommandDualParameter(object sender, EventArgs e)
        {
            if (sender is ToolStripMenuItem)
            {
                ToolStripMenuItem menu = (ToolStripMenuItem)sender;
                switch (menu.Name)
                {
                    case "runStepperMotorToolStripMenuItem":
                        frmUserDialog.setDialogBoxParameters("speed: [-248,+248], steps: [0,65535]", true, "#000", "00000");
                        break;
                }
                frmUserDialog.ShowDialog();
                if (frmUserDialog.DialogResult == System.Windows.Forms.DialogResult.OK)
                {
                    string userInput = null;

                    switch (menu.Name)
                    {
                        case "runStepperMotorToolStripMenuItem":
                            userInput = "$00RFJ" + frmUserDialog.getUserInput1() + " " + frmUserDialog.getUserInput2();
                            break;
                    }

                    if (userInput != null)
                    {
                        userInput = userInput.PadRight(37, '*');
                        RS232.WriteLine(userInput);
                    }
                }
            }
        }
    }
}
