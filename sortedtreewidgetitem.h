#ifndef SORTEDTREEWIDGETITEM_H
#define SORTEDTREEWIDGETITEM_H

#include <QTreeWidgetItem>

class SortedTreeWidgetItem : public QTreeWidgetItem
{
public:
    explicit SortedTreeWidgetItem();
private:
    bool operator<(const QTreeWidgetItem &other) const;

};

#endif // SORTEDTREEWIDGETITEM_H
