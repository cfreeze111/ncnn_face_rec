// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#ifndef NATIVEWINDOW_H
#define NATIVEWINDOW_H

#if defined(Q_OS_MACOS)
#  include <AppKit/AppKit.h>
#  define VIEW_BASE NSView
#elif defined(Q_OS_IOS)
#  include <UIKit/UIKit.h>
#  define VIEW_BASE UIView
#elif defined(Q_OS_WIN)
#  include <winuser.h>
#endif

class NativeWindow
{
    Q_DISABLE_COPY(NativeWindow)
public:
    NativeWindow();
    ~NativeWindow();

    operator WId() const { return reinterpret_cast<WId>(m_handle); }
    WId parentWinId() const;

    void setGeometry(const QRect &rect);
    QRect geometry() const;

private:
#if defined(Q_OS_MACOS) || defined(Q_OS_IOS)
    VIEW_BASE *m_handle = nullptr;
#elif defined(Q_OS_WIN)
    HWND m_handle = nullptr;
#endif
};

#if defined(Q_OS_MACOS) || defined(Q_OS_IOS)

@interface View : VIEW_BASE
@end

@implementation View
- (instancetype)init
{
    if ((self = [super init])) {
#if defined(Q_OS_MACOS)
        self.wantsLayer = YES;
#endif
        self.layer.backgroundColor = CGColorCreateGenericRGB(1.0, 0.5, 1.0, 1.0);
    }
    return self;
}

- (void)dealloc
{
    [super dealloc];
}
@end

NativeWindow::NativeWindow()
    : m_handle([View new])
{
}

NativeWindow::~NativeWindow()
{
    [m_handle release];
}

void NativeWindow::setGeometry(const QRect &rect)
{
    m_handle.frame = QRectF(rect).toCGRect();
}

QRect NativeWindow::geometry() const
{
    return QRectF::fromCGRect(m_handle.frame).toRect();
}

WId NativeWindow::parentWinId() const
{
    return WId(m_handle.superview);
}

#elif defined(Q_OS_WIN)

NativeWindow::NativeWindow()
{
    static const LPCWSTR className = []{
        WNDCLASS wc = {};
        wc.lpfnWndProc = DefWindowProc;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.lpszClassName = L"Native Window";
        wc.hbrBackground = CreateSolidBrush(RGB(255, 128, 255));
        RegisterClass(&wc);
        return wc.lpszClassName;
    }();
    m_handle = CreateWindowEx(0, className, nullptr, WS_POPUP,
                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
}

NativeWindow::~NativeWindow()
{
    DestroyWindow(m_handle);
}

void NativeWindow::setGeometry(const QRect &rect)
{
    MoveWindow(m_handle, rect.x(), rect.y(), rect.width(), rect.height(), false);
}

QRect NativeWindow::geometry() const
{
    WINDOWPLACEMENT wp;
    wp.length = sizeof(WINDOWPLACEMENT);
    if (GetWindowPlacement(m_handle, &wp)) {
        RECT r = wp.rcNormalPosition;
        return QRect(r.left, r.top, r.right - r.left, r.bottom - r.top);
    }
    return {};
}

WId NativeWindow::parentWinId() const
{
    return WId(GetAncestor(m_handle, GA_PARENT));
}

#endif

#endif // NATIVEWINDOW_H
