namespace ChessGame
{
    partial class ChessBoard
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.ResetBoard = new System.Windows.Forms.Button();
            this.Debug1 = new System.Windows.Forms.TextBox();
            this.Debug2 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // ResetBoard
            // 
            this.ResetBoard.Location = new System.Drawing.Point(1553, 150);
            this.ResetBoard.Name = "ResetBoard";
            this.ResetBoard.Size = new System.Drawing.Size(112, 34);
            this.ResetBoard.TabIndex = 0;
            this.ResetBoard.Text = "Reset";
            this.ResetBoard.UseVisualStyleBackColor = true;
            this.ResetBoard.Click += new System.EventHandler(this.ResetBoard_Click);
            // 
            // Debug1
            // 
            this.Debug1.Font = new System.Drawing.Font("Microsoft JhengHei UI", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.Debug1.Location = new System.Drawing.Point(1553, 64);
            this.Debug1.Name = "Debug1";
            this.Debug1.Size = new System.Drawing.Size(231, 58);
            this.Debug1.TabIndex = 1;
            // 
            // Debug2
            // 
            this.Debug2.Location = new System.Drawing.Point(1553, 454);
            this.Debug2.Name = "Debug2";
            this.Debug2.Size = new System.Drawing.Size(150, 30);
            this.Debug2.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(1553, 38);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(104, 23);
            this.label1.TabIndex = 3;
            this.label1.Text = "GameState";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(1553, 428);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(77, 23);
            this.label2.TabIndex = 4;
            this.label2.Text = "Debug1";
            // 
            // ChessBoard
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 23F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(2158, 1445);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Debug2);
            this.Controls.Add(this.Debug1);
            this.Controls.Add(this.ResetBoard);
            this.Name = "ChessBoard";
            this.Text = "ChessBoard";
            this.Load += new System.EventHandler(this.ChessBoard_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Button ResetBoard;
        private TextBox Debug1;
        private TextBox Debug2;
        private Label label1;
        private Label label2;
    }
}