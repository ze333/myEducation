using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace MouseClick
{
 public class Hook : IDisposable
    {
        #region Declare WinAPI functions
        [DllImport("kernel32.dll")]
        private static extern IntPtr LoadLibrary(string lpFileName);
 
        [DllImport("user32.dll")]
        private static extern IntPtr SetWindowsHookEx(int idHook, KeyboardHookProc callback, IntPtr hInstance, uint threadId);
        [DllImport("user32.dll")]
        private static extern IntPtr CallNextHookEx(IntPtr idHook, int nCode, int wParam, IntPtr lParam);
        [DllImport("user32.dll")]
        private static extern bool UnhookWindowsHookEx(IntPtr hInstance);
        #endregion
        #region Constants
        private const int WH_KEYBOARD_LL = 13;
        private const int WH_KEYDOWN = 0x0100;
        #endregion
 
        // код клавиши на которую ставим хук
        private int _key;
        public event KeyPressEventHandler KeyPressed;
 
        private delegate IntPtr KeyboardHookProc(int code, IntPtr wParam, IntPtr lParam);
        private KeyboardHookProc _proc;
        private IntPtr _hHook = IntPtr.Zero;
 
        public Hook(int keyCode)
        {
            _key = keyCode;
            _proc = HookProc;
        }
 
        public void SetHook()
        {
            var hInstance = LoadLibrary("User32");
            _hHook = SetWindowsHookEx(WH_KEYBOARD_LL, _proc, hInstance, 0);
        }
 
        public void Dispose()
        {
            UnHook();
        }
 
        public void UnHook()
        {
            UnhookWindowsHookEx(_hHook);
        }
 
        private IntPtr HookProc(int code, IntPtr wParam, IntPtr lParam)
        {
            if ((code >= 0 && wParam == (IntPtr)WH_KEYDOWN) && Marshal.ReadInt32(lParam) == _key)
            {
 
                // бросаем событие
                if (KeyPressed != null)
                {
                    KeyPressed(this, new KeyPressEventArgs(Convert.ToChar(code)));
                }
            }
 
            // пробрасываем хук дальше
            return CallNextHookEx(_hHook, code, (int)wParam, lParam);
        }
    }
}
