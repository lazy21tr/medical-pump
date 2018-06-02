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
    public partial class UserDialogForm : Form
    {
        public UserDialogForm()
        {
            InitializeComponent();
        }

        public string getUserInput1()
        {
            return mTxt1.Text;
        }

        public string getUserInput2()
        {
            return mTxt2.Text;
        }

        public void setDialogBoxParameters(string title, bool dualInput, string mask1, string mask2)
        {
            this.Text = title;
            this.mTxt2.Visible = dualInput;
            if (mask1 != null)
                mTxt1.Mask = mask1;
            if (mask2 != null)
                mTxt2.Mask = mask2;
        }
    }
}
