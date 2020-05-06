//
//  QtSLiMAppDelegate.h
//  SLiM
//
//  Created by Ben Haller on 7/13/2019.
//  Copyright (c) 2019-2020 Philipp Messer.  All rights reserved.
//	A product of the Messer Lab, http://messerlab.org/slim/
//

//	This file is part of SLiM.
//
//	SLiM is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
//	SLiM is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License along with SLiM.  If not, see <http://www.gnu.org/licenses/>.

#ifndef QTSLIMAPPDELEGATE_H
#define QTSLIMAPPDELEGATE_H

#include <QObject>
#include <QVector>
#include <QIcon>
#include <QPointer>
#include <string>

class QMenu;
class QAction;
class QtSLiMWindow;
class QtSLiMAppDelegate;
 

extern QtSLiMAppDelegate *qtSLiMAppDelegate;    // global instance

class QtSLiMAppDelegate : public QObject
{
    Q_OBJECT

    std::string app_cwd_;       // the app's current working directory
    bool launchedFromShell_;	// true if launched from shell, false if launched from Finder/other
    
    QIcon appIcon_;
    QIcon slimDocumentIcon_;
    QIcon genericDocumentIcon_;
    
public:
    explicit QtSLiMAppDelegate(QObject *parent);

    // Whether we were launched from a shell (true) or Finder/other (false)
    bool launchedFromShell(void) { return launchedFromShell_; }
    
    // The current working directory for the app
    std::string &QtSLiMCurrentWorkingDirectory(void) { return app_cwd_; }
    
    // Tracking the current active main window
    QtSLiMWindow *activeQtSLiMWindow(void);             // the frontmost window that is a QtSLiMWindow
    QWidget *activeWindow(void);                        // the frontmost window
    QWidget *activeWindowExcluding(QWidget *excluded);  // the frontmost window that is not excluded
    
    // Recipes menu
    void setUpRecipesMenu(QMenu *openRecipesSubmenu, QAction *findRecipeAction);

    // App-wide shared icons
    QIcon applicationIcon(void) { return appIcon_; }
    QIcon slimDocumentIcon(void) { return slimDocumentIcon_; }
    QIcon genericDocumentIcon(void) { return genericDocumentIcon_; }
    
public slots:
    void lastWindowClosed(void);
    void aboutToQuit(void);
    
    void findRecipe(void);
    void openRecipe(void);
    
signals:
    void modifiersChanged(Qt::KeyboardModifiers newModifiers);
    void activeWindowListChanged(void);
    
private:
    bool eventFilter(QObject *obj, QEvent *event) override;
    
    QVector<QPointer<QWidget>> focusedWindowList;       // a list of all windows, from front to back
    void pruneWindowList(void);                         // remove all windows that are closed or hidden
    bool queuedActiveWindowUpdate = false;
    
private slots:
    void focusChanged(QWidget *old, QWidget *now);
    void updateActiveWindowList(void);
};


#endif // QTSLIMAPPDELEGATE_H






































