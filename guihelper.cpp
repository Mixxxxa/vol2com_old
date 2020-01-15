// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "guihelper.h"

void clear(QActionGroup *group)
{
    if(!group)
        return;

    for(auto item : group->actions())
        group->removeAction(item);
    static_cast<QMenu*>(group->parent())->clear();
}

bool select(QComboBox *item, const QVariant &data)
{
    if(!item)
        return false;

    int ret = item->findData(data);
    if(ret == -1)
        return false;

    QSignalBlocker block(item);
    item->setCurrentIndex(ret);
    return true;
}

bool select(QActionGroup *item, const QVariant &data)
{
    if(!item)
        return false;

    const auto& actions = item->actions();
    auto it = std::find_if(actions.begin(), actions.end(), [&data](QAction* action)
    {
        return action->data() == data;
    });

    QSignalBlocker block(item);
    if(it != item->actions().end())
    {
        (*it)->setChecked(true);
        return true;
    }

    auto currentAction = item->checkedAction();
    if(currentAction)
        currentAction->setChecked(false);

    return false;
}

bool select(QSlider *item, const QVariant &data)
{
    if(!item)
        return false;

    bool check = false;
    auto value = data.toInt(&check);

    QSignalBlocker block(item);
    if(check && value >= item->minimum()
            && value <= item->maximum())
    {
        item->setValue(value);
        return true;
    }

    item->setValue(item->minimum());
    return false;
}
