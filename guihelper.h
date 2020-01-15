#ifndef GUIHELPER_H
#define GUIHELPER_H

#include <QComboBox>
#include <QSlider>
#include <QAction>
#include <QActionGroup>
#include <QVariant>
#include <QMenu>

template <class T1, class T2>
void fill(QActionGroup *group, const std::vector<std::pair<T1, T2> > &data)
{
    if(!group || !group->parent())
        return;

    auto parent = static_cast<QMenu*>(group->parent());

    for(const auto& item : data)
    {
        auto action = group->addAction(item.first);
        action->setData(item.second);
        action->setCheckable(true);
        parent->addAction(action);
    }
}

template <class T1, class T2>
void fill(QComboBox *combobox, const std::vector<std::pair<T1, T2> > &data)
{
    if(!combobox)
        return;

    combobox->setEnabled(false);

    for(const auto& item : data)
        combobox->addItem(item.first, item.second);

    combobox->setEnabled(true);
}

void clear(QActionGroup *group);

bool select(QComboBox *item, const QVariant& data);
bool select(QActionGroup *item, const QVariant& data);
bool select(QSlider *item, const QVariant& data);

#endif // GUIHELPER_H
