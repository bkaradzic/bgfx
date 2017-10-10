/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2012, assimp team

All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the following
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/

#if (!defined AV_LOG_WINDOW_H_INCLUDED)
#define AV_LOG_WINDOW_H_INCLUDE

namespace AssimpView
{


    //-------------------------------------------------------------------------------
    /** \brief Subclass of Assimp::LogStream used to add all log messages to the
     *         log window.
     */
    //-------------------------------------------------------------------------------
    class CMyLogStream : public Assimp::LogStream
    {
    public:
        /** @brief  Implementation of the abstract method   */
        void write( const char* message );
    };


    //-------------------------------------------------------------------------------
    /** \brief Class to display log strings in a separate window
    */
    //-------------------------------------------------------------------------------
    class CLogWindow
    {
    private:

        friend class CMyLogStream;
        friend INT_PTR CALLBACK LogDialogProc( HWND hwndDlg, UINT uMsg,
            WPARAM wParam, LPARAM lParam );

        CLogWindow() : hwnd( NULL ), bIsVisible( false ), bUpdate( true ) {}

    public:


        // Singleton accessors
        static CLogWindow s_cInstance;
        inline static CLogWindow& Instance()
        {
            return s_cInstance;
        }

        // initializes the log window
        void Init();

        // Shows the log window
        void Show();

        // Clears the log window
        void Clear();

        // Save the log window to an user-defined file
        void Save();

        // write a line to the log window
        void WriteLine( const char* message );

        // Set the bUpdate member
        inline void SetAutoUpdate( bool b )
        {
            this->bUpdate = b;
        }

        // updates the log file
        void Update();

    private:

        // Window handle
        HWND hwnd;

        // current text of the window (contains RTF tags)
        std::string szText;
        std::string szPlainText;

        // is the log window currently visible?
        bool bIsVisible;

        // Specified whether each new log message updates the log automatically
        bool bUpdate;


    public:
        // associated log stream
        CMyLogStream* pcStream;
    };

}

#endif // AV_LOG_DISPLA