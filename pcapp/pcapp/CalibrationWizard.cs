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
    public partial class CalibrationWizard : Form
    {
        int balancer = 0;
        double v0, v1, b0, b1, gain, offset;
        Int32 offsetRep, gainRep;
        public CalibrationWizard(int bal)
        {
            InitializeComponent();
            balancer = bal;
        }

        protected override void OnShown(EventArgs e)
        {
            btnNext.Text = "İleri";
            base.OnShown(e);
        }

        public void processMessage(string message) {
            if (message == "Done!")
            {
                tabControl1.SelectedIndex = (tabControl1.SelectedIndex + 1 < tabControl1.TabCount) ? tabControl1.SelectedIndex + 1 : tabControl1.SelectedIndex;
                btnNext.Enabled = true;
            }
            else if (message.StartsWith("BAL")) 
            {
                if (tabControl1.SelectedIndex == 1)
                {
                    b0 = double.Parse(message.Substring(5, message.Length - 6));
                    tabControl1.SelectedIndex = 2;
                    btnNext.Enabled = true;
                }
                else if (tabControl1.SelectedIndex == 2)
                {
                    b1 = double.Parse(message.Substring(5, message.Length - 6));
                    gain = 100 * (v1 - v0) / (b1 - b0);
                    gainRep = calculateGainRegValue(gain);
                    //MessageBox.Show(b0.ToString() + "," + b1.ToString() + "," + v0.ToString() + "," + v1.ToString() + "," + gain + "," + gainRep.ToString("X8"));
                    tabControl1.SelectedIndex = 3;
                    btnNext.Text = "Kapat";
                    btnNext.Enabled = true;
                }
            }
        }

        private void btnNext_Click(object sender, EventArgs e)
        {
            try
            {
                btnNext.Enabled = false;
                switch (tabControl1.SelectedIndex)
                {
                    case 0:
                        string command = (balancer == 1) ? "$00RFP---****----****----****----****" : "$00RFQ---****----****----****----****";
                        AppMainForm.getInstance().RS232.WriteLine(command);
                        lblPage1.Text = "Devrenin Cevabı Bekleniyor...(5 sn.)";
                        break;
                    case 1:
                        v0 = double.Parse(mTBPage2.Text);
                        command = (balancer == 1) ? "$00RFC---****----****----****----****" : "$00RFD---****----****----****----****";
                        AppMainForm.getInstance().RS232.WriteLine(command);
                        lblPage2.Text = "Devrenin Cevabı Bekleniyor...(5 sn.)";
                        break;
                    case 2:
                        v1 = double.Parse(mTBPage3.Text);
                        command = (balancer == 1) ? "$00RFC---****----****----****----****" : "$00RFD---****----****----****----****";
                        AppMainForm.getInstance().RS232.WriteLine(command);
                        lblPage2.Text = "Devrenin Cevabı Bekleniyor...(5 sn.)";
                        break;
                    case 3:
                        string gval = "$00RF";
                        if (balancer == 1)
                        {
                            gval += "T";
                        }
                        else
                        {
                            gval += "U";
                        }
                        gval += gainRep.ToString();
                        gval = gval.PadRight(37, '*');
                        AppMainForm.getInstance().RS232.WriteLine(gval);
                        this.Hide();
                        break;
                    default:
                        break;
                }
            }
            catch (Exception exc)
            {
                MessageBox.Show(exc.Message, "Hata", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }

        Int32 calculateGainRegValue(double gain)
        {
            Int32 retVal = 0;
            Int32 bit = 0x01000000;
            double x = 0;
            for (int i = 0; i > -25; --i)
            {
                double val = Math.Pow(2, i);
                if (x + val < gain)
                {
                    x += val;
                    retVal += bit;
                }
                bit >>= 1;
            }

            return retVal;
        }
    }

    class myTabControl : TabControl {
        protected override void WndProc(ref Message m)
        {
            // Hide tabs by trapping the TCM_ADJUSTRECT message
            if (m.Msg == 0x1328 && !DesignMode)
                m.Result = (IntPtr)1;
            else
                base.WndProc(ref m);
        }
    }
}
