/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "edge.h"
#include "node.h"


#include <QDebug>

#include <math.h>

#include <QPainter>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

//! [0]
Edge::Edge(Node *sourceNode, Node *destNode, qreal frequency)
	: arrowSize(10), mFrequency(frequency)
{
	setAcceptedMouseButtons(0);
	source = sourceNode;
	dest = destNode;
	source->addEdge(this);
	dest->addEdge(this);
	adjust();
}
//! [0]

//! [1]
Node *Edge::sourceNode() const
{
	return source;
}

Node *Edge::destNode() const
{
	return dest;
}
//! [1]

//! [2]
void Edge::adjust()
{
	if (!source || !dest)
		return;

	QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
	qreal length = line.length();

	prepareGeometryChange();

	if (length > qreal(20.)) {

		//		int sector = (line.p1().x() > line.p2().x() )
		//				? ((line.p1().y() > line.p2().y()) ? 2 : 3)
		//				: ((line.p1().y() > line.p2().y()) ? 1 : 4);


		qreal angleRect = atan(100/100)*180/Pi;//  h/w
		//angleRect = angleRect > 180? angleRect: angleRect -180;

		QLineF line1(line);


		if (( line.angle() <= angleRect) ||
				( line.angle() >= 180 - angleRect && line.angle() <= 180 + angleRect) ||
				( line.angle() >= 360 - angleRect))

			//if (line.angle()!= 90 && line.angle()!= 270)
			line1.setLength(50./cos(line.angle()*Pi/180));
		//	else line1.setLength(50);
		else
			//if (line.angle()!= 0 && line.angle()!= 180)
			line1.setLength(50./sin(line.angle()*Pi/180));
		//else line1.setLength(50);

		//		qDebug()<<"----";
		//		qDebug()<<line1.length();
		//		float f = line1.length();
		//		line1.setLength(50. / line.dx() * line.length());
		//		line1.setLength(f);
		//		qDebug()<<line.length();


		//qDebug()<<"------------";
		//qDebug()<<line1.length()<<" "<< 50*1.4 <<" "<<line.dx()<<" "<<line.dy();


		QPointF edgeOffset((line.dx() *line1.length()) / length,
						   (line.dy() *line1.length()) / length);
		sourcePoint = line.p1() + edgeOffset;
		destPoint = line.p2() - edgeOffset;
	} else {
		sourcePoint = destPoint = line.p1();
	}
}
//! [2]

//! [3]
QRectF Edge::boundingRect() const
{
	if (!source || !dest)
		return QRectF();

	qreal penWidth = 1;
	qreal extra = (penWidth + arrowSize) / 2.0 + 50;

	return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
									  destPoint.y() - sourcePoint.y()))
			.normalized()
			.adjusted(-extra, -extra, extra, extra);
}
//! [3]

//! [4]
void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	if (!source || !dest)
		return;

	QLineF line(sourcePoint, destPoint);
	if (qFuzzyCompare(line.length(), qreal(0.)))
		return;
	//! [4]

	//! [5]
	// Draw the line itself
	painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter->drawLine(line);
	//! [5]

	//! [6]
	// Draw the arrows
	double angle = acos(line.dx() / line.length());
	if (line.dy() >= 0)
		angle = TwoPi - angle;

	QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi / 3) * arrowSize,
											  cos(angle - Pi / 3) * arrowSize);
	QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
											  cos(angle - Pi + Pi / 3) * arrowSize);

	painter->setBrush(Qt::black);
	painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);

	painter->setBrush(Qt::NoBrush);
	QLineF line1(line);
	line1.setLength(line1.length() - 35);
	QRectF rect(line1.p2().rx() - 25,line1.p2().ry() - 25,50,50);


	QFont font = painter->font();
	font.setPointSize(font.pointSize() * 2);
	painter->setFont(font);

	painter->setBrush(Qt::white);
	painter->drawEllipse(rect);

    painter->drawText(rect.adjusted(5,12,0,0), QString::number(mFrequency,'f',2));
}
//! [6]
