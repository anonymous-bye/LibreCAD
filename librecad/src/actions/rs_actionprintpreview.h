/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2010 R. van Twisk (librecad@rvt.dds.nl)
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software 
** Foundation and appearing in the file gpl-2.0.txt included in the
** packaging of this file.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** This copyright notice MUST APPEAR in all copies of the script!  
**
**********************************************************************/

#ifndef RS_ACTIONPRINTPREVIEW_H
#define RS_ACTIONPRINTPREVIEW_H

#include <memory>

#include "rs_actioninterface.h"

class QG_PrintPreviewOptions;

/**
 * Default action for print preview.
 *
 * @author Andrew Mustun
 */
class RS_ActionPrintPreview : public RS_ActionInterface {
    Q_OBJECT
public:
    /**
     * Action States.
     */
    enum Status {
        Neutral,
        Moving
    };

public:
    RS_ActionPrintPreview(RS_EntityContainer& container,
                          RS_GraphicView& graphicView);
	~RS_ActionPrintPreview() override;

	void init(int status=0) override;
	void resume() override;

	void mouseMoveEvent(QMouseEvent* e) override;
	void mousePressEvent(QMouseEvent* e) override;
	void mouseReleaseEvent(QMouseEvent* e) override;

	void coordinateEvent(RS_CoordinateEvent* e) override;
	void commandEvent(RS_CommandEvent* e) override;
	QStringList getAvailableCommands() override;

	void showOptions() override;
	void hideOptions() override;

	void updateMouseCursor() override;

    void center();
    void fit();
    bool setScale(double f, bool autoZoom = true);
	double getScale() const;
    void printWarning(const QString& s);
    void calcPagesNum();

    void setLineWidthScaling(bool state);
	void setBlackWhite(bool bw);
    RS2::Unit getUnit();
    void setPaperScaleFixed(bool fixed);
    bool getPaperScaleFixed();

    void setOption(std::unique_ptr<QG_PrintPreviewOptions> option);
    std::unique_ptr<QG_PrintPreviewOptions>& getOption();

private:

    bool hasOptions = false;
    bool m_bPaperOffset = false;
	struct Points;
	std::unique_ptr<Points> pPoints;
    std::unique_ptr<QG_PrintPreviewOptions> m_option;
};

#endif
