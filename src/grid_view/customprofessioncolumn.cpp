/*
Dwarf Therapist
Copyright (c) 2009 Trey Stout (chmod)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "customprofessioncolumn.h"
#include "superlaborcolumn.h"
#include "columntypes.h"
#include "viewcolumnset.h"
#include "gamedatareader.h"
#include "dwarfmodel.h"
#include "truncatingfilelogger.h"
#include "superlabor.h"
#include "dwarftherapist.h"
#include "dwarf.h"
#include "labor.h"

CustomProfessionColumn::CustomProfessionColumn(const QString &title, QString id, ViewColumnSet *set, QObject *parent)
    : SuperLaborColumn(title,id,set,parent)
{
    m_type = CT_CUSTOM_PROFESSION;
}

CustomProfessionColumn::CustomProfessionColumn(QSettings &s, ViewColumnSet *set, QObject *parent)
    : SuperLaborColumn(s,set,parent)
{
    m_type = CT_CUSTOM_PROFESSION;
}

CustomProfessionColumn::CustomProfessionColumn(const CustomProfessionColumn &to_copy)
    : SuperLaborColumn(to_copy)
{
    m_type = CT_CUSTOM_PROFESSION;
}

QStandardItem *CustomProfessionColumn::build_cell(Dwarf *d) {
    QStandardItem *item = init_cell(d);

    item->setData(CT_CUSTOM_PROFESSION, DwarfModel::DR_COL_TYPE);
    LaborListBase *ml = DT->get_custom_profession(m_id);

    if(!ml){
        item->setData("", DwarfModel::DR_CUSTOM_PROF);
        item->setData(-1, DwarfModel::DR_RATING);
        item->setData(-1, DwarfModel::DR_DISPLAY_RATING);
        item->setData(-1,DwarfModel::DR_LABORS);
        item->setToolTip(tr("Unknown super labor."));
        return item;
    }else{
        float rating = ml->get_skill_rating(d->id());
        item->setData(rating, DwarfModel::DR_RATING);
        item->setData(rating, DwarfModel::DR_DISPLAY_RATING);
        item->setData(ml->get_name(), DwarfModel::DR_CUSTOM_PROF);
        item->setData(ml->get_converted_labors(),DwarfModel::DR_LABORS);
    }

    item->setToolTip(build_tooltip(d,ml));

    return item;
}

float CustomProfessionColumn::get_rating(int id, LaborListBase::LLB_RATING_TYPE type){
    float m_sort_val = 0.0;
    //SuperLabor *sl = DT->get_super_labor(m_id);
    LaborListBase *ml = DT->get_custom_profession(m_id);
    if(ml)
        m_sort_val = ml->get_rating(id,type);
    return m_sort_val;
}

QStandardItem *CustomProfessionColumn::build_aggregate(const QString &group_name, const QVector<Dwarf*> &dwarves){
    Q_UNUSED(dwarves);
    QStandardItem *item = init_aggregate(group_name);
    return item;
}

