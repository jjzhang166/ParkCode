namespace WcfRoadHost
{
    partial class RoadForm
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
            this.btnClearLog = new System.Windows.Forms.Button();
            this.timerReconnect = new System.Windows.Forms.Timer(this.components);
            this.txtLog = new System.Windows.Forms.RichTextBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.btnGetFeeRate = new System.Windows.Forms.Button();
            this.panel2 = new System.Windows.Forms.Panel();
            this.timerUploadData = new System.Windows.Forms.Timer(this.components);
            this.timerClear = new System.Windows.Forms.Timer(this.components);
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnClearLog
            // 
            this.btnClearLog.Location = new System.Drawing.Point(8, 8);
            this.btnClearLog.Name = "btnClearLog";
            this.btnClearLog.Size = new System.Drawing.Size(75, 23);
            this.btnClearLog.TabIndex = 0;
            this.btnClearLog.Text = "清除日志";
            this.btnClearLog.UseVisualStyleBackColor = true;
            this.btnClearLog.Click += new System.EventHandler(this.btnClearLog_Click);
            // 
            // timerReconnect
            // 
            this.timerReconnect.Interval = 10000;
            this.timerReconnect.Tick += new System.EventHandler(this.timerReconnect_Tick);
            // 
            // txtLog
            // 
            this.txtLog.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtLog.Location = new System.Drawing.Point(0, 0);
            this.txtLog.Name = "txtLog";
            this.txtLog.ReadOnly = true;
            this.txtLog.Size = new System.Drawing.Size(792, 530);
            this.txtLog.TabIndex = 2;
            this.txtLog.Text = "";
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.btnGetFeeRate);
            this.panel1.Controls.Add(this.btnClearLog);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(792, 36);
            this.panel1.TabIndex = 3;
            // 
            // btnGetFeeRate
            // 
            this.btnGetFeeRate.Location = new System.Drawing.Point(88, 8);
            this.btnGetFeeRate.Name = "btnGetFeeRate";
            this.btnGetFeeRate.Size = new System.Drawing.Size(75, 23);
            this.btnGetFeeRate.TabIndex = 1;
            this.btnGetFeeRate.Text = "获取费率";
            this.btnGetFeeRate.UseVisualStyleBackColor = true;
            this.btnGetFeeRate.Click += new System.EventHandler(this.btnGetFeeRate_Click);
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.txtLog);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(0, 36);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(792, 530);
            this.panel2.TabIndex = 4;
            // 
            // timerUploadData
            // 
            this.timerUploadData.Interval = 60000;
            this.timerUploadData.Tick += new System.EventHandler(this.timerUploadData_Tick);
            // 
            // timerClear
            // 
            this.timerClear.Interval = 86400000;
            this.timerClear.Tick += new System.EventHandler(this.timerClear_Tick);
            // 
            // RoadForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(792, 566);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.Name = "RoadForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "路边Web Service";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.RoadForm_FormClosing);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.RoadForm_FormClosed);
            this.Load += new System.EventHandler(this.RoadForm_Load);
            this.panel1.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnClearLog;
        private System.Windows.Forms.Timer timerReconnect;
        private System.Windows.Forms.RichTextBox txtLog;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Timer timerUploadData;
        private System.Windows.Forms.Button btnGetFeeRate;
        private System.Windows.Forms.Timer timerClear;
    }
}

