namespace ChessGame
{
    public partial class ChessBoard : Form
    {
        const int BOARD_SIZE = 8;
        const int SQUARE_NUM = BOARD_SIZE * BOARD_SIZE;
        const int SQUARE_LENGTH = 170;
        const int MARGIN = 50;
        const int PIECE_TYPE = 13;
        Color CLR_DARK = Color.FromArgb(118, 150, 86);
        Color CLR_LIGHT = Color.White;
        Color CLR_SELECT = Color.LightGoldenrodYellow;

        Button[,] m_ChessButtons = new Button[BOARD_SIZE, BOARD_SIZE];
        Image[] m_imgPiece = new Image[PIECE_TYPE];
        string m_PngDir = Directory.GetParent(Directory.GetCurrentDirectory()).Parent.Parent.FullName + "\\png";
        int m_ChessButtonStartInd;
        int m_ValidStartPieceInd;
        int[] m_PieceType = new int[SQUARE_NUM];

        private enum EPlayerType : int
        {
            White = 0,
            Black
        }

        private enum EPieceType : int
        {
            None = 0,
            W_Pawn,
            W_Knight,
            W_Bishop,
            W_Rook,
            W_Queen,
            W_King,
            B_Pawn,
            B_Knight,
            B_Bishop,
            B_Rook,
            B_Queen,
            B_King,
        }


        public ChessBoard()
        {
            InitializeComponent();
            loadImage();
            m_ValidStartPieceInd = -1;
            m_ChessButtonStartInd = 0;
        }

        private void loadImage()
        {
            m_imgPiece[(int)EPieceType.None] = null;
            m_imgPiece[(int)EPieceType.W_Pawn] = Image.FromFile(m_PngDir + "\\pawn_white.png");
            m_imgPiece[(int)EPieceType.W_Knight] = Image.FromFile(m_PngDir + "\\knight_white.png");
            m_imgPiece[(int)EPieceType.W_Bishop] = Image.FromFile(m_PngDir + "\\bishop_white.png");
            m_imgPiece[(int)EPieceType.W_Rook] = Image.FromFile(m_PngDir + "\\rook_white.png");
            m_imgPiece[(int)EPieceType.W_Queen] = Image.FromFile(m_PngDir + "\\queen_white.png");
            m_imgPiece[(int)EPieceType.W_King] = Image.FromFile(m_PngDir + "\\king_white.png");

            m_imgPiece[(int)EPieceType.B_Pawn] = Image.FromFile(m_PngDir + "\\pawn_black.png");
            m_imgPiece[(int)EPieceType.B_Knight] = Image.FromFile(m_PngDir + "\\knight_black.png");
            m_imgPiece[(int)EPieceType.B_Bishop] = Image.FromFile(m_PngDir + "\\bishop_black.png");
            m_imgPiece[(int)EPieceType.B_Rook] = Image.FromFile(m_PngDir + "\\rook_black.png");
            m_imgPiece[(int)EPieceType.B_Queen] = Image.FromFile(m_PngDir + "\\queen_black.png");
            m_imgPiece[(int)EPieceType.B_King] = Image.FromFile(m_PngDir + "\\king_black.png");
        }

        private void ChessBoard_Load(object sender, EventArgs e)
        {
            // record the starting index of chess button controls
            m_ChessButtonStartInd = Controls.Count;

            // draw the board
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                int left = MARGIN;
                int top = SQUARE_LENGTH * (BOARD_SIZE - i - 1) + MARGIN;
                for (int j = 0; j < BOARD_SIZE; j++)
                {
                    m_ChessButtons[i, j] = new Button();
                    m_ChessButtons[i, j].Name = "S" + (i * BOARD_SIZE + j).ToString();
                    m_ChessButtons[i, j].Height = SQUARE_LENGTH;
                    m_ChessButtons[i, j].Width = SQUARE_LENGTH;
                    m_ChessButtons[i, j].Top = top;
                    m_ChessButtons[i, j].Left = left;
                    m_ChessButtons[i, j].Click += ChessBoard_Click;
                    m_ChessButtons[i, j].BackColor = (i + j) % 2 == 0 ? CLR_DARK : CLR_LIGHT;
                    Controls.Add(m_ChessButtons[i, j]);

                    left += SQUARE_LENGTH;
                }
            }

            // put chess piece on board
            resetChessBoard();
        }

        private void resetChessBoard()
        {
            int Index = 0;

            // assign white pieces
            m_PieceType[Index++] = (int)EPieceType.W_Rook;
            m_PieceType[Index++] = (int)EPieceType.W_Knight;
            m_PieceType[Index++] = (int)EPieceType.W_Bishop;
            m_PieceType[Index++] = (int)EPieceType.W_Queen;
            m_PieceType[Index++] = (int)EPieceType.W_King;
            m_PieceType[Index++] = (int)EPieceType.W_Bishop;
            m_PieceType[Index++] = (int)EPieceType.W_Knight;
            m_PieceType[Index++] = (int)EPieceType.W_Rook;
            for (int i = 0; i < 8; i++) m_PieceType[Index++] = (int)EPieceType.W_Pawn;

            // assign black pieces
            for (int i = 0; i < 32; i++) m_PieceType[Index++] = (int)EPieceType.None;

            // assign black pieces
            for (int i = 0; i < 8; i++) m_PieceType[Index++] = (int)EPieceType.B_Pawn;
            m_PieceType[Index++] = (int)EPieceType.B_Rook;
            m_PieceType[Index++] = (int)EPieceType.B_Knight;
            m_PieceType[Index++] = (int)EPieceType.B_Bishop;
            m_PieceType[Index++] = (int)EPieceType.B_Queen;
            m_PieceType[Index++] = (int)EPieceType.B_King;
            m_PieceType[Index++] = (int)EPieceType.B_Bishop;
            m_PieceType[Index++] = (int)EPieceType.B_Knight;
            m_PieceType[Index++] = (int)EPieceType.B_Rook;

            // update chess board images according to m_PieceType
            updateChessBoard();
        }

        private void updateChessBoard()
        {
            // reset all 64 chess button images by starting from chess button starting index controls
            for (int i = 0; i < SQUARE_NUM; i++)
            {
                (Controls[m_ChessButtonStartInd + i] as Button).Image = m_imgPiece[m_PieceType[i]];
            }
        }

        private void updateOnePiece(int Ind)
        {
            (Controls[m_ChessButtonStartInd + Ind] as Button).Image = m_imgPiece[m_PieceType[Ind]];
        }

        private void chooseStartPiece(int Ind)
        {
            // start piece not yet pressed, record the index only when starting index position has a piece
            if (m_PieceType[Ind] != (int)EPieceType.None)
            {
                m_ValidStartPieceInd = Ind;
                // change button background color
                (Controls[m_ChessButtonStartInd + Ind] as Button).BackColor = CLR_SELECT;
            }            
        }

        private void chooseTargetPiece(int Ind)
        {
            Debug2.Text = "From " + m_ValidStartPieceInd.ToString() + " To " + Ind.ToString();

            // move a piece to target
            relocatePiece(m_ValidStartPieceInd, Ind);

            // back color of starting index resumes to be default
            (Controls[m_ChessButtonStartInd + m_ValidStartPieceInd] as Button).BackColor = (m_ValidStartPieceInd / BOARD_SIZE + m_ValidStartPieceInd % BOARD_SIZE) % 2 == 0 ? CLR_DARK : CLR_LIGHT;
            m_ValidStartPieceInd = -1;
        }

        private void ChessBoard_Click(object? sender, EventArgs e)
        {
            string ButtonName = (sender as Button).Name;
            int ButtonInd = Int32.Parse(ButtonName.Substring(1));

            // act differently depends if it is a start or target click
            if (m_ValidStartPieceInd == -1)
            {
                chooseStartPiece(ButtonInd);
            }
            else
            {
                chooseTargetPiece(ButtonInd);
            }
        }

        private void relocatePiece(int StartInd, int TargetInd)
        {
            if (StartInd == TargetInd) return;

            m_PieceType[TargetInd] = m_PieceType[StartInd];
            m_PieceType[StartInd] = (int)EPieceType.None;

            updateOnePiece(StartInd);
            updateOnePiece(TargetInd);
        }

        private void ResetBoard_Click(object sender, EventArgs e)
        {
            resetChessBoard();
        }
    }
}