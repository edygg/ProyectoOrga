#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    init_components();
}

MainWindow::~MainWindow()
{
}

void MainWindow::init_components() {
    init_actions();
    init_field_dialog();
    init_change_field_dialog();
    init_input_record_dialog();

    /* File menu */
    QMenu* file_menu = menuBar()->addMenu("File");
    file_menu->addAction(this->new_file);
    file_menu->addAction(this->open_file);
    file_menu->addAction(this->save_file);
    file_menu->addAction(this->print_file);
    file_menu->addAction(this->close_file);
    file_menu->addAction(this->quit_program);

    /* Field menu */
    QMenu* field_menu = menuBar()->addMenu("Fields");
    field_menu->addAction(this->create_field);
    field_menu->addAction(this->change_field);
    field_menu->addAction(this->list_fields);

    /* Record menu */
    QMenu* record_menu = menuBar()->addMenu("Records");
    record_menu->addAction(this->insert_record);
    record_menu->addAction(this->search_record);
    record_menu->addAction(this->delete_record);
    record_menu->addAction(this->list_records);
    record_menu->addAction(this->compact_file);
    record_menu->addAction(this->cross_tables);

    /* Indexes menu */
    QMenu* indexes_menu = menuBar()->addMenu("Indexes");
    indexes_menu->addAction(this->create_simple_index);
    indexes_menu->addAction(this->create_Btree_index);
    indexes_menu->addAction(this->reindex);

    /* Utilities menu */
    QMenu* utilities_menu = menuBar()->addMenu("Utilities");
    utilities_menu->addAction(this->export_xml);
    utilities_menu->addAction(this->import_xml);
    utilities_menu->addAction(this->export_json);
    utilities_menu->addAction(this->import_json);

    /* Status bar */
    QLabel* main_status_bar = new QLabel();
    this->lbl_status_bar = main_status_bar;
    main_status_bar->setAlignment(Qt::AlignHCenter);
    main_status_bar->setMinimumSize(main_status_bar->sizeHint());
    this->statusBar()->addWidget(main_status_bar);

    /* Main table */
    this->main_table = new QTableWidget(this);
    this->main_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setCentralWidget(main_table);

    initialStatus();
    this->setMinimumSize(500, 500);
    this->setWindowTitle(PROGRAM_NAME);
}

void MainWindow::init_actions() {
    /* File menu actions */
    this->new_file = new QAction("New File", this);
    this->new_file->setShortcut(Qt::CTRL + Qt::Key_N);
    this->new_file->setStatusTip("Create a new database");
    this->new_file->setToolTip("Create a new database");
    this->new_file->setCheckable(false);
    connect(this->new_file, SIGNAL(triggered()), this, SLOT(newFile()));

    this->open_file = new QAction("Open File", this);
    this->open_file->setShortcut(Qt::CTRL + Qt::Key_O);
    this->open_file->setStatusTip("Open an exist database");
    this->open_file->setToolTip("Open an exist database");
    this->open_file->setCheckable(false);
    connect(this->open_file, SIGNAL(triggered()), this, SLOT(openFile()));

    this->save_file = new QAction("Save File", this);
    this->save_file->setShortcut(Qt::CTRL + Qt::Key_S);
    this->save_file->setStatusTip("Save changes in the current database");
    this->save_file->setToolTip("Save changes in the current database");
    this->save_file->setCheckable(false);
    connect(this->save_file, SIGNAL(triggered()), this, SLOT(saveFile()));

    this->print_file = new QAction("Print File", this);
    this->print_file->setShortcut(Qt::CTRL + Qt::Key_P);
    this->print_file->setStatusTip("Print the content of file");
    this->print_file->setToolTip("Print the content of file");
    this->print_file->setCheckable(false);
    connect(this->print_file, SIGNAL(triggered()), this, SLOT(printFile()));

    this->close_file = new QAction("Close File", this);
    this->close_file->setShortcut(Qt::CTRL + Qt::Key_C);
    this->close_file->setStatusTip("Close the current database");
    this->close_file->setToolTip("Close the current database");
    this->close_file->setCheckable(false);
    connect(this->close_file, SIGNAL(triggered()), this, SLOT(closeFile()));

    this->quit_program = new QAction("Quit", this);
    this->quit_program->setShortcut(Qt::ALT + Qt::Key_F4);
    this->quit_program->setStatusTip("Exit program");
    this->quit_program->setToolTip("Exit program");
    this->quit_program->setCheckable(false);
    connect(this->quit_program, SIGNAL(triggered()), this, SLOT(close()));

    /* Field menu actions */
    this->create_field = new QAction("Create", this);
    this->create_field->setStatusTip("Create a new field");
    this->create_field->setToolTip("Create a new field");
    this->create_field->setCheckable(false);
    connect(this->create_field, SIGNAL(triggered()), this, SLOT(createField()));

    this->change_field = new QAction("Change", this);
    this->change_field->setStatusTip("Change a exist field");
    this->change_field->setToolTip("Change a exist field");
    this->change_field->setCheckable(false);
    connect(this->change_field, SIGNAL(triggered()), this, SLOT(changeField()));

    this->list_fields = new QAction("List", this);
    this->list_fields->setStatusTip("List all fields");
    this->list_fields->setToolTip("List all fields");
    this->list_fields->setCheckable(false);
    connect(this->list_fields, SIGNAL(triggered()), this, SLOT(listFields()));

    /* Record menu actions */
    this->insert_record = new QAction("Insert", this);
    this->insert_record->setStatusTip("Insert a new record");
    this->insert_record->setToolTip("Insert a new record");
    this->insert_record->setCheckable(false);
    connect(this->insert_record, SIGNAL(triggered()), this, SLOT(insertRecord()));

    this->search_record = new QAction("Search", this);
    this->search_record->setStatusTip("Search a record");
    this->search_record->setToolTip("Search a record");
    this->search_record->setCheckable(false);
    connect(this->search_record, SIGNAL(triggered()), this, SLOT(searchRecord()));

    this->delete_record = new QAction("Delete", this);
    this->delete_record->setStatusTip("Delete a record");
    this->delete_record->setToolTip("Delete a record");
    this->delete_record->setCheckable(false);
    connect(this->delete_record, SIGNAL(triggered()), this, SLOT(deleteRecord()));

    this->list_records = new QAction("List", this);
    this->list_records->setStatusTip("List all records");
    this->list_records->setToolTip("Search all records");
    this->list_records->setCheckable(false);
    connect(this->list_records, SIGNAL(triggered()), this, SLOT(listRecords()));

    this->compact_file = new QAction("Compact", this);
    this->compact_file->setStatusTip("Remove deleted elements in current file");
    this->compact_file->setToolTip("Remove deleted elements in current file");
    this->compact_file->setCheckable(false);
    connect(this->compact_file, SIGNAL(triggered()), this, SLOT(compactFile()));

    this->cross_tables = new QAction("Cross", this);
    this->cross_tables->setStatusTip("Cross tables");
    this->cross_tables->setToolTip("Cross tables");
    this->cross_tables->setCheckable(false);

    /* Indexes menu */
    this->create_simple_index = new QAction("Create Simple Index", this);
    this->create_simple_index->setStatusTip("Create Simple Index");
    this->create_simple_index->setToolTip("Create Simple Index");
    this->create_simple_index->setCheckable(false);
    connect(this->create_simple_index, SIGNAL(triggered()), this, SLOT(createSimpleIndex()));

    this->create_Btree_index = new QAction("Create B Tree Index", this);
    this->create_Btree_index->setStatusTip("Create B Tree Index");
    this->create_Btree_index->setToolTip("Create B Tree Index");
    this->create_Btree_index->setCheckable(false);

    this->reindex = new QAction("Reindex", this);
    this->reindex->setStatusTip("Reindex");
    this->reindex->setToolTip("Reindex");
    this->reindex->setCheckable(false);

    /* Utilities menu */
    this->export_xml = new QAction("Export to XML", this);
    this->export_xml->setStatusTip("Export current database intro XML file");
    this->export_xml->setToolTip("Export current database intro XML file");
    this->export_xml->setCheckable(false);
    connect(this->export_xml, SIGNAL(triggered()), this, SLOT(exportXml()));

    this->import_xml = new QAction("Import to XML", this);
    this->import_xml->setStatusTip("Import data intro XML file");
    this->import_xml->setToolTip("Import data intro XML file");
    this->import_xml->setCheckable(false);
    connect(this->import_xml, SIGNAL(triggered()), this, SLOT(importXml()));

    this->export_json = new QAction("Export to JSON", this);
    this->export_json->setStatusTip("Export current database intro JSON file");
    this->export_json->setToolTip("Export current database intro JSON file");
    this->export_json->setCheckable(false);
    connect(this->export_json, SIGNAL(triggered()), this, SLOT(exportJson()));

    this->import_json = new QAction("Import to JSON", this);
    this->import_json->setStatusTip("Import data intro JSON file");
    this->import_json->setToolTip("Import data intro JSON file");
    this->import_json->setCheckable(false);
}

void MainWindow::init_input_record_dialog() {
    this->input_record_dialog = new QDialog(this);
    QVBoxLayout* layout = new QVBoxLayout(this->input_record_dialog);
    this->lbl_message = new QLabel(this->input_record_dialog);
    layout->addWidget(this->lbl_message);
    this->le_input_data = new QLineEdit(this->input_record_dialog);
    layout->addWidget(this->le_input_data);
    this->btn_accept = new QPushButton("Add", this->input_record_dialog);
    connect(this->btn_accept, SIGNAL(clicked()), this, SLOT(recieveInput()));
    layout->addWidget(this->btn_accept);
}

void MainWindow::init_field_dialog() {
    this->field_dialog = new QDialog(this);
    QFormLayout* layout = new QFormLayout(this->field_dialog);

    this->le_name = new QLineEdit(this->field_dialog);
    this->le_name->setMaxLength(30);
    QRegExp exp("[A-Za-z][A-Za-z0-9]*");
    this->le_name->setValidator(new QRegExpValidator(exp, this->field_dialog));
    layout->addRow(new QLabel("Name"), this->le_name);

    QStringList cbox_options;
    cbox_options << "Integer" << "Real" << "String";
    this->cbox_datatype = new QComboBox(this->field_dialog);
    this->cbox_datatype->addItems(cbox_options);
    connect(this->cbox_datatype, SIGNAL(currentIndexChanged(QString)), this, SLOT(desactivateDecimalPlaces()));
    layout->addRow(new QLabel("Data Type"), this->cbox_datatype);

    this->sp_length = new QSpinBox(this->field_dialog);
    this->sp_length->setMinimum(1);
    this->sp_length->setMaximum(255);
    layout->addRow(new QLabel("Length"), this->sp_length);

    this->sp_decimal_places = new QSpinBox(this->field_dialog);
    this->sp_decimal_places->setMinimum(0);
    this->sp_decimal_places->setMaximum(255);
    this->sp_decimal_places->setEnabled(false);
    layout->addRow(new QLabel("Decimal Places"), this->sp_decimal_places);

    this->chbox_key = new QCheckBox(this->field_dialog);
    layout->addRow(new QLabel("Key"), this->chbox_key);

    QPushButton* btn_cancel = new QPushButton("Cancel", this->field_dialog);
    connect(btn_cancel, SIGNAL(clicked()), this->field_dialog, SLOT(close()));
    QPushButton* btn_save_field = new QPushButton("Save", this->field_dialog);
    connect(btn_save_field, SIGNAL(clicked()), this, SLOT(saveField()));
    layout->addWidget(btn_save_field);
    layout->addWidget(btn_cancel);



    this->field_dialog->setLayout(layout);

    this->field_dialog->setWindowTitle("Create a new field");
    this->field_dialog->setModal(true);
    this->field_dialog->setWindowFlags((windowFlags() | Qt::CustomizeWindowHint)
                                       & ~Qt::WindowMaximizeButtonHint
                                       & ~Qt::WindowContextHelpButtonHint
                                       & ~Qt::WindowMinimizeButtonHint);

}

void MainWindow::init_change_field_dialog() {
    this->change_field_dialog = new QDialog(this, (windowFlags() | Qt::CustomizeWindowHint)
                                            & ~Qt::WindowMaximizeButtonHint
                                            & ~Qt::WindowContextHelpButtonHint
                                            & ~Qt::WindowMinimizeButtonHint);
    QVBoxLayout* layout = new QVBoxLayout(this->change_field_dialog);

    this->cbox_fields = new QComboBox(this->change_field_dialog);
    layout->addWidget(this->cbox_fields);
    layout->addWidget(new QLabel("New name:", this->change_field_dialog));
    this->le_new_field_name = new QLineEdit(this->change_field_dialog);
    this->le_new_field_name->setMaxLength(FIELD_LENGTH);
    QRegExp exp("[A-Za-z][A-Za-z0-9]*");
    this->le_new_field_name->setValidator(new QRegExpValidator(exp, this->change_field_dialog));
    layout->addWidget(this->le_new_field_name);
    QPushButton* btn_change = new QPushButton("Change" ,this->change_field_dialog);
    connect(btn_change, SIGNAL(clicked()), this, SLOT(updateFields()));
    layout->addWidget(btn_change);
    this->change_field_dialog->setLayout(layout);

}

void MainWindow::desactivateDecimalPlaces() {
    if (this->cbox_datatype->currentText() != "Real") {
        this->sp_decimal_places->setEnabled(false);
    } else {
        this->sp_decimal_places->setEnabled(true);
    }
}

void MainWindow::initialStatus() {
    this->save_file->setEnabled(false);
    this->print_file->setEnabled(false);
    this->close_file->setEnabled(false);
    this->create_field->setEnabled(false);
    this->change_field->setEnabled(false);
    this->list_fields->setEnabled(false);
    this->insert_record->setEnabled(false);
    this->search_record->setEnabled(false);
    this->delete_record->setEnabled(false);
    this->list_records->setEnabled(false);
    this->compact_file->setEnabled(false);
    this->cross_tables->setEnabled(false);
    this->create_simple_index->setEnabled(false);
    this->create_Btree_index->setEnabled(false);
    this->reindex->setEnabled(false);
    this->export_xml->setEnabled(false);
    //this->import_xml->setEnabled(false);
    this->export_json->setEnabled(false);
    //this->import_json->setEnabled(false);
}

void MainWindow::enabledComponents() {
    this->save_file->setEnabled(true);
    this->print_file->setEnabled(true);
    this->close_file->setEnabled(true);
    this->create_field->setEnabled(true);
    this->change_field->setEnabled(true);
    this->list_fields->setEnabled(true);
    this->compact_file->setEnabled(true);
    this->insert_record->setEnabled(true);
    this->search_record->setEnabled(true);
    this->delete_record->setEnabled(true);
    this->list_records->setEnabled(true);
    this->cross_tables->setEnabled(true);
    this->create_simple_index->setEnabled(true);
    this->create_Btree_index->setEnabled(true);
    this->reindex->setEnabled(true);
    this->export_xml->setEnabled(true);
    //this->import_xml->setEnabled(true);
    this->export_json->setEnabled(true);
    //this->import_json->setEnabled(true);
}

void MainWindow::newFile() {
    QString folder = QFileDialog::getExistingDirectory(this, "New File", "");
    if (!folder.isEmpty()) {
        bool ok;
        QString file_name = QInputDialog::getText(this, "File name", "File Name: ", QLineEdit::Normal,"", &ok);
        if (ok && !file_name.isEmpty()) {
            if (this->current_open_file.isOpen()) {
                this->current_open_file.close();
            }

            QString path = folder + "/" + file_name + EXTENSION;
            if (!this->current_open_file.open(path.toStdString())) {
                this->current_open_file.open(path.toStdString(), ios::out);
                this->current_open_file.write("%", 1);
                this->current_open_file.flush();
                this->current_open_file.close();
                if(this->current_open_file.open(path.toStdString())) {
                    QMessageBox::information(this, "Successful", "Database created successfully");
                    enabledComponents();
                }
            }
        }
    }
}

void MainWindow::openFile() {
    QString file_name = QFileDialog::getOpenFileName(this, "Open File", "", "Databases (*" + EXTENSION + ")");

    if (!file_name.isEmpty()) {
        if (this->current_open_file.isOpen()) {
            this->current_open_file.close();
        }

        if (this->current_open_file.open(file_name.toStdString())) {
            this->lbl_status_bar->setText("Opened sucessfully");
            enabledComponents();
        } else {
            this->lbl_status_bar->setText("Error opening file");
        }
    }
}

void MainWindow::saveFile() {
    if(this->current_open_file.flush()) {
        this->lbl_status_bar->setText("Saved successfully");
    } else {
        this->lbl_status_bar->setText("Error saving file");
    }

}

void MainWindow::printFile() {
    QString folder = QFileDialog::getExistingDirectory(this, "Print PDF file", "");
    if (!folder.isEmpty()) {
        folder += "/outputTable.pdf";
        QString html_code = "";

        html_code += "<table border=\"1\">";
        html_code += "<tr>";

        vector<Field*> fields = this->current_open_file.listFields();

        for (int i = 0; i < fields.size(); i++) {
            Field* curr_f = fields[i];

            html_code += QString::fromStdString(string("<th>")) + QString::fromStdString(curr_f->getName()) + QString::fromStdString(string("</th>"));
        }

        html_code += "</tr>";

        vector<PrimaryIndex*> indexes = this->current_open_file.getAllIndexes();

        for (int i = 0; i < indexes.size(); i++) {
            PrimaryIndex* curr_i = indexes[i];
            Record* curr_r = this->current_open_file.readRecord(curr_i);
            vector<string> re = curr_r->getRecord();
            html_code += "<tr>";

            for (int j = 0; j < re.size(); j++) {
                html_code += QString::fromStdString(string("<td>")) + QString::fromStdString(re[j]) + QString::fromStdString(string("</td>"));
            }

            html_code += "</tr>";
        }

        html_code += "</table>";


        QTextDocument doc;
        doc.setHtml(html_code);
        QPrinter printer;
        printer.setOutputFileName(folder);
        printer.setOutputFormat(QPrinter::PdfFormat);
        doc.print(&printer);
        printer.newPage();
    }

}

void MainWindow::closeFile() {
    if (this->current_open_file.close()) {
        this->lbl_status_bar->setText("Closed successfully");
        initialStatus();
    } else {
        this->lbl_status_bar->setText("Error closing file");
    }
}

void MainWindow::createField() {
    this->field_dialog->exec();
}

void MainWindow::saveField() {
    if (this->le_name->text().isEmpty() || (this->sp_decimal_places->isEnabled() && this->sp_decimal_places->value() >= this->sp_length->value())) {
        QMessageBox::warning(this->field_dialog, "Error", "Check field values");
    } else {
        Field* neo;

        if (this->cbox_datatype->currentText() == "Integer") {
            neo = new Field(
                        this->le_name->text().toStdString(),
                        INT_DT,
                        this->sp_length->value(),
                        255,
                        this->chbox_key->checkState()
                        );
            this->current_open_file.createField(neo);
            this->lbl_status_bar->setText("Success");
        } else if (this->cbox_datatype->currentText() == "String") {
            neo = new Field(
                        this->le_name->text().toStdString(),
                        STRING_DT,
                        this->sp_length->value(),
                        255,
                        this->chbox_key->checkState()
                        );
            this->current_open_file.createField(neo);
            this->lbl_status_bar->setText("Success");
        } else {
            neo = new Field(
                        this->le_name->text().toStdString(),
                        REAL_DT,
                        this->sp_length->value(),
                        this->sp_decimal_places->value(),
                        this->chbox_key->checkState()
                        );
            this->current_open_file.createField(neo);
            this->lbl_status_bar->setText("Success");
        }

        this->le_name->setText("");
        this->sp_length->setValue(1);
        this->sp_decimal_places->setValue(0);
    }
}

void MainWindow::changeField() {
    this->cbox_fields->clear();
    vector<Field*> all_fields = this->current_open_file.listFields();

    if (all_fields.size() != 0) {
        for (int i = 0; i < all_fields.size(); i++) {
            Field* current_field = all_fields[i];
            QString op = QString::fromStdString(current_field->getName());
            this->cbox_fields->addItem(op);
        }
        this->change_field_dialog->exec();
    } else {
        QMessageBox::critical(this, "No fields found", "There are no fields");
    }
}

void MainWindow::updateFields() {
    QString selected_field = this->cbox_fields->currentText();
    vector<Field*> f = this->current_open_file.listFields();
    for (int i = 0; i < f.size(); i++) {
        Field* curr = f[i];
        if (QString::fromStdString(curr->getName()) == selected_field) {
            curr->setName(this->le_new_field_name->text().toStdString());
            break;
        }
    }
    this->le_new_field_name->setText("");
    this->current_open_file.rewriteFields();
    this->lbl_status_bar->setText("Success");
    this->change_field_dialog->close();
}

void MainWindow::listFields() {
    this->clearMainTable();

    vector<Field*> fields = this->current_open_file.listFields();
    this->main_table->setColumnCount(5);
    QStringList headers;
    headers << "Name" << "Data Type" << "Length" << "Decimal Places" << "Key";
    this->main_table->setHorizontalHeaderLabels(headers);
    this->main_table->setRowCount(fields.size());

    for (int i = 0; i < fields.size(); i++) {
        stringstream ss;
        string value;
        QString value2;
        Field* curr = fields[i];
        ss << curr->getName();
        ss >> value;
        value2 = QString::fromStdString(value);
        this->main_table->setItem(i, 0, new QTableWidgetItem(value2));

        if (curr->getDatatype() == INT_DT) {
            value2 = "INTEGER";
        } else if (curr->getDatatype() == STRING_DT) {
            value2 = "STRING";
        } else {
            value2 = "REAL";
        }
        this->main_table->setItem(i, 1, new QTableWidgetItem(value2));

        value2 = QString::number((int) curr->getLength());
        this->main_table->setItem(i, 2, new QTableWidgetItem(value2));

        if (curr->getDatatype() != REAL_DT) {
            value2 = "0";
        } else {
            value2 = QString::number((int) curr->getDecimalPlaces());
        }
        this->main_table->setItem(i, 3, new QTableWidgetItem(value2));

        if (curr->isKey()) {
            value2 = "Yes";
        } else {
            value2 = "No";
        }
        this->main_table->setItem(i, 4, new QTableWidgetItem(value2));
    }
}

void MainWindow::clearMainTable() {
    if (!this->main_table) {
        return;
    }

    while(this->main_table->rowCount() > 0) {
        this->main_table->removeRow(0);
    }

    while (this->main_table->columnCount() > 0) {
        this->main_table->removeColumn(0);
    }
}

void MainWindow::insertRecord() {
    vector<Field*> fields = this->current_open_file.listFields();
    vector<string> record;
    this->current_open_file.loadSimpleIndexes();
    if (fields.size() == 0) {
        QMessageBox::information(this, "Error", "There are no fields");
    }

    for (int i = 0; i < fields.size(); i++) {
        Field* curr_f = fields[i];

        this->lbl_message->setText(QString::fromStdString(curr_f->getName()));
        this->le_input_data->setMaxLength(curr_f->getLength());
        this->le_input_data->setText("");
        this->str_input_data = "";
        stringstream regular_pattern;

        if (curr_f->getDatatype() == INT_DT) {
            regular_pattern << "[0-9]*";
        } else if (curr_f->getDatatype() == REAL_DT) {
            regular_pattern << "[0-9]*\.[0-9]{1,";
            regular_pattern << curr_f->getDecimalPlaces();
            regular_pattern << "}";
        } else {
            regular_pattern << "[A-Za-z0-9]*";
        }

        QRegExp exp(QString::fromStdString(regular_pattern.str()));
        this->le_input_data->setValidator(new QRegExpValidator(exp, this->input_record_dialog));

        this->input_record_dialog->exec();

        if (this->str_input_data.isEmpty()) {
            return;
        }

        record.push_back(this->str_input_data.toStdString());
    }
    Record r(fields, record);
    if (this->current_open_file.addRecord(r)) {
        this->lbl_status_bar->setText("Record added");
    } else {
        this->lbl_status_bar->setText("Error adding record");
    }
}

void MainWindow::searchRecord() {
    vector<Field*> fields = this->current_open_file.listFields();
    stringstream k;

    for (int i = 0; i < fields.size(); i++) {
        Field* curr_f = fields[i];

        if (curr_f->isKey()) {
            this->lbl_message->setText(QString::fromStdString(curr_f->getName()));
            this->le_input_data->setMaxLength(curr_f->getLength());
            this->le_input_data->setText("");
            this->str_input_data = "";
            stringstream regular_pattern;

            if (curr_f->getDatatype() == INT_DT) {
                regular_pattern << "[0-9]*";
            } else if (curr_f->getDatatype() == REAL_DT) {
                regular_pattern << "[0-9]*\.[0-9]{1,";
                regular_pattern << curr_f->getDecimalPlaces();
                regular_pattern << "}";
            } else {
                regular_pattern << "[A-Za-z0-9]*";
            }

            QRegExp exp(QString::fromStdString(regular_pattern.str()));
            this->le_input_data->setValidator(new QRegExpValidator(exp, this->input_record_dialog));

            this->input_record_dialog->exec();

            if (this->str_input_data.isEmpty()) {
                return;
            }

            k << this->str_input_data.toStdString();
        }
    }

    PrimaryIndex* result_index = this->current_open_file.searchRecord(k.str());

    if (result_index == NULL) {
        QMessageBox::information(this, "Not Found", "The record doesn't exist");
    } else {
        Record* result_record = this->current_open_file.readRecord(result_index);

        this->clearMainTable();
        vector<Field*> fields = result_record->getFields();
        this->main_table->setColumnCount(fields.size());
        QStringList headers;

        for (int i = 0; i < fields.size(); i++) {
            Field* curr_f = fields[i];
            headers << QString::fromStdString(curr_f->getName());
        }

        this->main_table->setHorizontalHeaderLabels(headers);
        this->main_table->setRowCount(1);

        vector<string> re = result_record->getRecord();

        for (int j = 0; j < re.size(); j++) {
            this->main_table->setItem(0, j, new QTableWidgetItem(QString::fromStdString(re.at(j))));
        }

    }

}

void MainWindow::deleteRecord() {
    vector<Field*> fields = this->current_open_file.listFields();
    stringstream k;

    for (int i = 0; i < fields.size(); i++){
        Field* curr_f = fields[i];

        if (curr_f->isKey()) {
            this->lbl_message->setText(QString::fromStdString(curr_f->getName()));
            this->le_input_data->setMaxLength(curr_f->getLength());
            this->le_input_data->setText("");
            this->str_input_data = "";
            stringstream regular_pattern;

            if (curr_f->getDatatype() == INT_DT) {
                regular_pattern << "[0-9]*";
            } else if (curr_f->getDatatype() == REAL_DT) {
                regular_pattern << "[0-9]*\.[0-9]{1,";
                regular_pattern << curr_f->getDecimalPlaces();
                regular_pattern << "}";
            } else {
                regular_pattern << "[A-Za-z0-9]*";
            }

            QRegExp exp(QString::fromStdString(regular_pattern.str()));
            this->le_input_data->setValidator(new QRegExpValidator(exp, this->input_record_dialog));

            this->input_record_dialog->exec();

            if (this->str_input_data.isEmpty()) {
                return;
            }

            k << this->str_input_data.toStdString();
        }
    }

    if (this->current_open_file.deleteRecord(k.str())) {
        this->lbl_status_bar->setText("Deleted success");
    } else {
        QMessageBox::information(this, "Error", "The record doesn't exists");
    }
}

void MainWindow::listRecords() {
    vector<PrimaryIndex*> indexes = this->current_open_file.getAllIndexes();

    this->clearMainTable();
    vector<Field*> fields = this->current_open_file.listFields();
    this->main_table->setColumnCount(fields.size());
    QStringList headers;

    for (int i = 0; i < fields.size(); i++) {
        Field* curr_f = fields[i];
        headers << QString::fromStdString(curr_f->getName());
    }

    this->main_table->setHorizontalHeaderLabels(headers);
    this->main_table->setRowCount(indexes.size());

    for (int i = 0; i < indexes.size(); i++) {
        PrimaryIndex* curr_i = indexes[i];

        Record* curr_r = this->current_open_file.readRecord(curr_i);
        vector<string> re = curr_r->getRecord();

        for (int j = 0; j < re.size(); j++) {
            this->main_table->setItem(i, j, new QTableWidgetItem(QString::fromStdString(re.at(j))));
        }
    }
}

void MainWindow::compactFile() {
    this->current_open_file.compact();
}

void MainWindow::createSimpleIndex() {
    this->current_open_file.loadSimpleIndexes();
}

void MainWindow::recieveInput() {
    if (this->le_input_data->text().isEmpty()) {
        QMessageBox::information(this->input_record_dialog, "Error", "Empty Input Data");
    } else {
        this->str_input_data = this->le_input_data->text();
        this->input_record_dialog->close();
    }
}

void MainWindow::exportXml() {
    QString file_path = QFileDialog::getExistingDirectory(this, "Export to XML file", "");

    if (!file_path.isEmpty()) {
        file_path += "/outputXML.xml";

        QFile file(file_path);

        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::warning(this, "Error", "Can not export file");
        } else {
            QXmlStreamWriter xml_writer;
            xml_writer.setDevice(&file);
            xml_writer.writeStartDocument();

            xml_writer.writeStartElement("database");
            vector<PrimaryIndex*> indexes = this->current_open_file.getAllIndexes();

            for (int i = 0; i < indexes.size(); i++) {
                PrimaryIndex* curr_i = indexes[i];
                Record* curr_r = this->current_open_file.readRecord(curr_i);
                vector<Field*> fields = curr_r->getFields();
                vector<string> record = curr_r->getRecord();

                xml_writer.writeStartElement("record");

                for (int j = 0; j < fields.size(); j++) {
                    Field* curr_f = fields[j];

                    xml_writer.writeStartElement(QString::fromStdString(curr_f->getName()));

                    if (curr_f->isKey()) {
                        xml_writer.writeAttribute(QString::fromStdString(string("key")), QString::fromStdString(string("true")));
                    } else {
                        xml_writer.writeAttribute(QString::fromStdString(string("key")), QString::fromStdString(string("false")));
                    }

                    if (curr_f->getDatatype() == INT_DT) {
                        xml_writer.writeAttribute(QString::fromStdString(string("type")), QString::fromStdString(string("INT")));
                        xml_writer.writeAttribute(QString::fromStdString(string("length")), QString::number(curr_f->getLength()));
                    } else if (curr_f->getDatatype() == STRING_DT) {
                        xml_writer.writeAttribute(QString::fromStdString(string("type")), QString::fromStdString(string("STRING")));
                        xml_writer.writeAttribute(QString::fromStdString(string("length")), QString::number(curr_f->getLength()));
                    } else {
                        xml_writer.writeAttribute(QString::fromStdString(string("type")), QString::fromStdString(string("REAL")));
                        xml_writer.writeAttribute(QString::fromStdString(string("length")), QString::number(curr_f->getLength()));
                        xml_writer.writeAttribute(QString::fromStdString(string("dplaces")), QString::number(curr_f->getDecimalPlaces()));
                    }

                    xml_writer.writeCharacters(QString::fromStdString(record[j]));
                    xml_writer.writeEndElement();
                }
                xml_writer.writeEndElement();

            }
            xml_writer.writeEndElement();
            xml_writer.writeEndDocument();

        }
    }
}

void MainWindow::exportJson() {
    QString file_path = QFileDialog::getExistingDirectory(this, "Export JSON file", "");

    if (!file_path.isEmpty()) {
        file_path += "/outputJSON.json";

        QFile file(file_path);

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Can not export the file");
        } else {
            QJsonDocument doc;
            QJsonObject root;

            vector<PrimaryIndex*> indexes = this->current_open_file.getAllIndexes();

            for (int i = 0; i < indexes.size(); i++) {
                QJsonObject curr_o;
                PrimaryIndex* curr_i = indexes[i];
                Record* curr_r = this->current_open_file.readRecord(curr_i);
                vector<Field*> fields = curr_r->getFields();
                vector<string> record = curr_r->getRecord();

                for (int j = 0; j < fields.size(); j++) {
                    Field* curr_f = fields[j];
                    curr_o.insert(QString::fromStdString(curr_f->getName()), QJsonValue(QString::fromStdString(record[j])));
                }
                root.insert(QString::fromStdString(string("Record")) + QString::number(i), QJsonValue(curr_o));
            }

            doc.setObject(root);
            QString result(doc.toJson());

            QTextStream out(&file);

            out << result;
        }
    }
}

void MainWindow::importXml() {
    QString file_name = QFileDialog::getOpenFileName(this, "Import XML file", "", "XML (*.xml)");

    if (!file_name.isEmpty()) {
        this->newFile();
        QDomDocument doc;
        QFile input_file(file_name);
        if (!input_file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, "Error", "Can not import this file");
            return;
        }

        if (!doc.setContent(&input_file)) {
             QMessageBox::warning(this, "Error", "Can not import this file");
            return;
        }

        QDomElement db = doc.documentElement();

        QDomNode fr = db.firstChild().firstChild();

        QDomElement e = fr.toElement();

        while (!e.isNull()) {
            QString name = e.tagName();

            if (!e.hasAttributes()) {
                QMessageBox::warning(this, "Error", "Incorrect data structure");
                return;
            }

            QDomNamedNodeMap map = e.attributes();
            datatype dt;
            int length;
            int dp = 0;
            bool k = false;

            if (map.size() < 3) {
                QMessageBox::warning(this, "Error", "Incorrect data structure");
                return;
            }

            for (int i = 0; i < map.size(); i++) {
                if (!map.item(i).isNull()) {
                    QDomNode tmpn = map.item(i);
                    QDomAttr attr = tmpn.toAttr();

                    if (attr.name() == "key") {
                        if (attr.value() == "true") {
                            k = true;
                        }
                    } else if (attr.name() == "type") {
                        if (attr.value() == "INT") {
                            dt = INT_DT;
                        } else if (attr.value() == "REAL") {
                            dt = REAL_DT;
                        } else {
                            dt = STRING_DT;
                        }
                    } else if (attr.name() == "length") {
                        length = attr.value().toInt();
                    } else if (attr.name() == "dplaces") {
                        dp = attr.value().toInt();
                    } else {
                        QMessageBox::warning(this, "Error", "Incorrect data structure");
                        return;
                    }
                } else {
                    QMessageBox::warning(this, "Error", "Incorrect data structure");
                    return;
                }
            }

            Field* neo = new Field(name.toStdString(), dt, length, dp, k);
            this->current_open_file.createField(neo);
            e = e.nextSibling().toElement();
        }
        cout << endl;
        input_file.close();
    }
}
