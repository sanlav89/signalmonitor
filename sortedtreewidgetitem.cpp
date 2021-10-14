#include "sortedtreewidgetitem.h"
#include <QCollator>

SortedTreeWidgetItem::SortedTreeWidgetItem() : QTreeWidgetItem()
{
}

bool SortedTreeWidgetItem::operator<(const QTreeWidgetItem &other) const
{
    int column = treeWidget() ? treeWidget()->sortColumn() : 0;
    QCollator collator;
    collator.setNumericMode( true );
    return collator.compare( text( column ), other.text( column ) ) < 0;
}
