using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lotto
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Clear()
        {
            label1.Text = "...";
            label2.Text = "...";
            label3.Text = "...";
            label4.Text = "...";
            label5.Text = "...";
            label6.Text = "...";
            BtnPick.Enabled = true;
            BtnReset.Enabled = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Clear();
        }

        private void BtnReset_Click(object sender, EventArgs e)
        {
            // Reset Button & Label state to Start. 
            Clear();
        }

        private void BtnPick_Click(object sender, EventArgs e)
        {
            // Create a random number generator object.  
            Random rnd = new Random();

            // Create an array to hold numbers 1-59.
            int[] seq = new int[59];

            // Fill array elements 0-58 with numbers 1-59.
            for (int i = 1; i < 60; i++) seq[i - 1] = i;

            // Shuffle the values in all array elements.
            for (int i = 0; i < 59; i++)
            {
                int j = (rnd.Next() % 59);
                int k = seq[i]; seq[i] = seq[j]; seq[j] = k;
            }

            // Display the values in array elements 1-6.
            label1.Text = seq[1].ToString();
            label2.Text = seq[2].ToString();
            label3.Text = seq[3].ToString();
            label4.Text = seq[4].ToString();
            label5.Text = seq[5].ToString();
            label6.Text = seq[6].ToString();

            // Set the Button state to Done.
            BtnPick.Enabled = false;
            BtnReset.Enabled = true;
        }
    }
}