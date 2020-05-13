#ifndef GET_TOOL_H
#define GET_TOOL_H

#include <QDialog>

namespace Ui {
class Get_tool;
}

class Get_tool : public QDialog
{
    Q_OBJECT

public:
    explicit Get_tool(QWidget *parent = nullptr);
    ~Get_tool();

private:
    Ui::Get_tool *ui;
};

#endif // GET_TOOL_H
