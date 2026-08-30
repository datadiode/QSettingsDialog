#include "settingslistedit.h"
#include "settingsdisplaydialog.h"
#include "ui_settingslistedit.h"

ListEditWidget::ListEditWidget(const QStringList &stringList, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SettingsListEdit),
	model(new QStringListModel(stringList, this))
{
	this->ui->setupUi(this);

	this->ui->actionAdd->setIcon(QIcon(SettingsDisplayDialog::tr(":/QSettingsDialog/icons/add.ico")));
	this->ui->actionRemove->setIcon(QIcon(SettingsDisplayDialog::tr(":/QSettingsDialog/icons/delete.ico")));
	this->ui->actionMove_Up->setIcon(QIcon(SettingsDisplayDialog::tr(":/QSettingsDialog/icons/up.ico")));
	this->ui->actionMove_Down->setIcon(QIcon(SettingsDisplayDialog::tr(":/QSettingsDialog/icons/down.ico")));

	this->ui->listView->setModel(this->model);

	this->ui->actionRemove->setShortcut(QKeySequence::Delete);
	QAction *seperator = new QAction(this);
	seperator->setSeparator(true);
	this->ui->listView->addActions({
									   this->ui->actionAdd,
									   this->ui->actionRemove,
									   seperator,
									   this->ui->actionMove_Up,
									   this->ui->actionMove_Down
								   });
	this->ui->addButton->setDefaultAction(this->ui->actionAdd);
	this->ui->removeButton->setDefaultAction(this->ui->actionRemove);
	this->ui->moveUpButton->setDefaultAction(this->ui->actionMove_Up);
	this->ui->moveDownButton->setDefaultAction(this->ui->actionMove_Down);

	connect(this->model, &QStringListModel::dataChanged,
			this, &ListEditWidget::modelChanged);
	connect(this->model, &QStringListModel::rowsInserted,
			this, &ListEditWidget::modelChanged);
	connect(this->model, &QStringListModel::rowsRemoved,
			this, &ListEditWidget::modelChanged);
}

ListEditWidget::ListEditWidget(QWidget *parent) :
	ListEditWidget(QStringList(), parent)
{}

ListEditWidget::~ListEditWidget()
{
	delete this->ui;
}

bool ListEditWidget::areButtonsVisible() const
{
	return this->ui->buttonContainerWidget->isVisible();
}

QStringList ListEditWidget::stringList() const
{
	return this->model->stringList();
}

void ListEditWidget::setButtonsVisible(bool buttonsVisible)
{
	this->ui->buttonContainerWidget->setVisible(buttonsVisible);
}

void ListEditWidget::setStringList(QStringList stringList)
{
	if (this->model->stringList() == stringList)
		return;

	this->model->setStringList(stringList);
	emit stringListChanged(stringList);
}

void ListEditWidget::clear()
{
	this->model->setStringList(QStringList());
}

void ListEditWidget::modelChanged()
{
	emit stringListChanged(this->model->stringList());
}

void ListEditWidget::on_actionAdd_triggered()
{
	int row = this->ui->listView->currentIndex().row() + 1;
	this->model->insertRow(row);
	QModelIndex newIndex = this->model->index(row);
	this->ui->listView->setCurrentIndex(newIndex);
	this->ui->listView->edit(newIndex);
}

void ListEditWidget::on_actionRemove_triggered()
{
	QModelIndex index = this->ui->listView->currentIndex();
	if(index.isValid())
		this->model->removeRow(index.row());
}

void ListEditWidget::on_actionMove_Up_triggered()
{
	int row = this->ui->listView->currentIndex().row();
	if(row > 0) {
		QStringList list = this->model->stringList();
		list.move(row, row - 1);
		this->model->setStringList(list);
		this->ui->listView->setCurrentIndex(this->model->index(row - 1));
		emit stringListChanged(list);
	}
}

void ListEditWidget::on_actionMove_Down_triggered()
{
	int row = this->ui->listView->currentIndex().row();
	QStringList list = this->model->stringList();
	if(row < list.size() - 1) {
		list.move(row, row + 1);
		this->model->setStringList(list);
		this->ui->listView->setCurrentIndex(this->model->index(row + 1));
		emit stringListChanged(list);
	}
}



SettingsListEditWidget::SettingsListEditWidget(QWidget *parent) :
	QSettingsWidget(parent)
{}

void SettingsListEditWidget::setValue(const QVariant &value)
{
	this->setStringList(value.toStringList());
}

QVariant SettingsListEditWidget::getValue() const
{
	return this->stringList();
}

void SettingsListEditWidget::resetValue()
{
	this->clear();
}
