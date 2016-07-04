using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MouseClick
{
    public partial class Form1 : Form
    {
        private bool swi;
        private Hook _hook;

        [DllImport("user32.dll")]
        static extern void keybd_event(byte bVk, byte bScan, uint dwFlags, UIntPtr dwExtraInfo);
 
        [DllImport("user32.dll")]//Импортируем перемещение курсора
        public static extern void SetCursorPos(int x, int y);
        [DllImport("user32.dll")]//Импортируем нажатия мыши
        static extern void mouse_event(int dwFlags, int dx, int dy, int dwData, int dwExtraInfo);
        [Flags]
        public enum MouseEventFlags
        {
            LEFTDOWN = 0x00000002,
            LEFTUP = 0x00000004,
            MIDDLEDOWN = 0x00000020,
            MIDDLEUP = 0x00000040,
            MOVE = 0x00000001,
            ABSOLUTE = 0x00008000,
            RIGHTDOWN = 0x00000008,
            RIGHTUP = 0x00000010
        }
        const int WH_KEYBOARD_LL = 13; // Номер глобального LowLevel-хука на клавиатуру
        const int WM_KEYDOWN = 0x100; // Сообщения нажатия клавиши
        public Form1()
        {
            InitializeComponent();
            keybd_event(0x90, 0x45, 0x1, (UIntPtr)0);

            // 0x90 клавиша NumLock
            _hook = new Hook(0x70); //Передаем код клавиши на которую ставим хук, тут это CapsLock

            _hook.KeyPressed += new KeyPressEventHandler(_hook_KeyPressed);
            _hook.SetHook();
            //while (swi)
            //{
            //    mouse_event((int)(MouseEventFlags.LEFTDOWN), 940, 470, 0, 0);
            //    System.Threading.Thread.Sleep(1);
            //    // отпускаем левую кнопку
            //    mouse_event((int)(MouseEventFlags.LEFTUP), 940, 470, 0, 0); 
            //}

 
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            //mouse_event((int)(MouseEventFlags.LEFTDOWN), 940, 470, 0, 0);
            //System.Threading.Thread.Sleep(0);
            //// отпускаем левую кнопку
          
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //timer1.Start();
            swi = !swi;

        }
        void _hook_KeyPressed(object sender, KeyPressEventArgs e) //Событие нажатия клавиш
        {
            swi = !swi;
            //timer1.Enabled = !timer1.Enabled;
            Mouseclick();
        }

        void Mouseclick()
        {
            while (swi)
            {
                if (swi == true)
                {
                    mouse_event((int)(MouseEventFlags.LEFTDOWN), 940, 470, 0, 0);
                    System.Threading.Thread.Sleep(1);
                    // отпускаем левую кнопку
                    mouse_event((int)(MouseEventFlags.LEFTUP), 940, 470, 0, 0);
                    Application.DoEvents();

                }
                else
                {
                    break;

                }

            }
        }

    }
}
