#include "mainwindow.h"

/**
 * Contructor de la clase MainWindow
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    init_components();
}

/**
 * Destructor de la clase MainWindow
 */
MainWindow::~MainWindow()
{
}

/**
 * Método que incializa todos los componentes gŕaficos de la ventana
 */
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

/**
 * Método que se encarga de inicializar las acciones u opciones de todos
 * los menús de la interfaz gráfica.
 */
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

    this->import_xml = new QAction("Import from XML", this);
    this->import_xml->setStatusTip("Import data intro XML file");
    this->import_xml->setToolTip("Import data intro XML file");
    this->import_xml->setCheckable(false);
    connect(this->import_xml, SIGNAL(triggered()), this, SLOT(importXml()));

    this->export_json = new QAction("Export to JSON", this);
    this->export_json->setStatusTip("Export current database intro JSON file");
    this->export_json->setToolTip("Export current database intro JSON file");
    this->export_json->setCheckable(false);
    connect(this->export_json, SIGNAL(triggered()), this, SLOT(exportJson()));

    this->import_json = new QAction("Import from JSON", this);
    this->import_json->setStatusTip("Import data intro JSON file");
    this->import_json->setToolTip("Import data intro JSON file");
    this->import_json->setCheckable(false);
    connect(this->import_json, SIGNAL(triggered()), this, SLOT(importJson()));
}

/**
 * Método que se encarga de inicializar los compopnentes gráficos de la ventana
 * de ingreso de registros
 */
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

/**
 * Método que se encarga de inicializar los componentes gráficos de la ventana
 * de ingreso de campos.
 */
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

    QPushButton* btn_cancel = new QPushButton("Close", this->field_dialog);
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

/**
 * Método que se encarga de desactivar el ingreso de espacios decimales
 * en los casos donde no se requiera el uso.
 */
void MainWindow::desactivateDecimalPlaces() {
    if (this->cbox_datatype->currentText() != "Real") {
        this->sp_decimal_places->setEnabled(false);
    } else {
        this->sp_decimal_places->setEnabled(true);
    }
}

/**
 * Método que se encarga de desactivar las opciones de menú innecesarias
 * para comenzar a utilizar el programa
 */
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
    this->export_json->setEnabled(false);
}

/**
 * Método que reactiva las opciones de menú para comenzar a utilizar el
 * programa.
 */
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
    this->export_json->setEnabled(true);
}

/**
 * Método que se encarga de crear un nuevo archivo y abrirlo para su uso en el programa
 */
void MainWindow::newFile() {
    //Abre un dialogo para seleccionar la carpeta donde se guardará el archivo
    QString folder = QFileDialog::getExistingDirectory(this, "New File", "");
    if (!folder.isEmpty()) { // si el usuario no canceló el dialogo
        bool ok;
        //se piede al usuario el nombre del archivo
        QString file_name = QInputDialog::getText(this, "File name", "File Name: ", QLineEdit::Normal,"", &ok);
        //si no canceló y si colocó un nombre
        if (ok && !file_name.isEmpty()) {
            //se procede a cerrar cualquier otro archivo abierto
            if (this->current_open_file.isOpen()) {
                this->current_open_file.close();
            }

            //se concatena el nombre del archivo en la carpeta correspondiente
            QString path = folder + "/" + file_name + EXTENSION;
            //se abre el archivo
            if (!this->current_open_file.open(path.toStdString())) {
                this->current_open_file.open(path.toStdString(), ios::out);
                // se escribe un % para identificar que es un nuevo archivo
                this->current_open_file.write("%", 1);
                this->current_open_file.flush();
                this->current_open_file.close();
                if(this->current_open_file.open(path.toStdString())) {
                    // se abrió y creo exitosamente
                    QMessageBox::information(this, "Successful", "Database created successfully");
                    enabledComponents();
                }
            }
        }
    }
}

/**
 * Método encargado de abrir archivos de registros ya existentes
 */
void MainWindow::openFile() {
    //Abre el cuadro de diálogo para abrir un archivo existente
    QString file_name = QFileDialog::getOpenFileName(this, "Open File", "", "Databases (*" + EXTENSION + ")");

    if (!file_name.isEmpty()) { //si el usuario no cerró el dialogo
        // se cierra cualquier otro archivo que estaba abierto
        if (this->current_open_file.isOpen()) {
            this->current_open_file.close();
        }

        // se abre el archivo y se habilitan los componentes de los menús
        if (this->current_open_file.open(file_name.toStdString())) {
            this->lbl_status_bar->setText("Opened sucessfully");
            enabledComponents();
        } else {
            this->lbl_status_bar->setText("Error opening file");
        }
    }
}

/**
 * Método que se encarga de guardar el archivo a través de una llamada a
 * flush.
 */
void MainWindow::saveFile() {
    if(this->current_open_file.flush()) {
        this->lbl_status_bar->setText("Saved successfully");
    } else {
        this->lbl_status_bar->setText("Error saving file");
    }

}

/**
 * Método que imprime el archivo actual de registros en un archivo PDF
 */
void MainWindow::printFile() {
    //si no hay campos o registros se evita la impresión
    if (this->current_open_file.listFields().size() == 0 || this->current_open_file.getAllIndexes().size() == 0) {
        this->lbl_status_bar->setText("There are no fields or records");
        return;
    }

    //se abre un dialogo para que el usuario seleccione donde guardar el archivo
    QString folder = QFileDialog::getExistingDirectory(this, "Print PDF file", "");
    if (!folder.isEmpty()) { // si el usuario no precionó cancelar
        //concatena el nuevo nombre del archivo a la carpeta seleccionada
        folder += "/outputTable.pdf";
        //crea un string para colocar el código HTML que será reinterpretado
        //para impimir tablas en el PDF
        QString html_code = "";

        //Crea una tabla
        html_code += "<table border=\"1\">";
        html_code += "<tr>";

        //Añade los campos a la tabla en la primer fila
        vector<Field*> fields = this->current_open_file.listFields();

        for (int i = 0; i < fields.size(); i++) {
            Field* curr_f = fields[i];

            html_code += QString::fromStdString(string("<th>")) + QString::fromStdString(curr_f->getName()) + QString::fromStdString(string("</th>"));
        }

        html_code += "</tr>";

        vector<PrimaryIndex*> indexes = this->current_open_file.getAllIndexes();

        //Comienza a añadir los registros a la tabla
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

        //cierra la tabla terminada
        html_code += "</table>";

        //abre un documento de texto
        QTextDocument doc;
        //asigna el código HTML
        doc.setHtml(html_code);
        //crea una impresora y la habilita para imprimir en PDF
        QPrinter printer;
        printer.setOutputFileName(folder);
        printer.setOutputFormat(QPrinter::PdfFormat);
        doc.print(&printer);
        //crea la nueva página terminada
        printer.newPage();
        this->lbl_status_bar->setText("Print successful");
    }

}

/**
 * Método que cierra un archivo de registros abierto y desactiva los componentes
 * de los menús.
 */
void MainWindow::closeFile() {
    if (this->current_open_file.close()) {
        this->lbl_status_bar->setText("Closed successfully");
        initialStatus();
    } else {
        this->lbl_status_bar->setText("Error closing file");
    }
}

/**
 * Método encargado de levantar la ventana que crea campos. Si ya exiten
 * registros en el archivo no es posible crear más campos.
 */
void MainWindow::createField() {
    if (this->current_open_file.getAllIndexes().size() > 0) {
        this->lbl_status_bar->setText("Can not add more fields");
        return;
    }
    this->field_dialog->exec();
}

/**
 * Método que envía la información obtenida de un campo a través de las ventanas
 * al archivo de registros
 */
void MainWindow::saveField() {
    //verifica que se le haya asignado un nombre al campo y que si aplica los espacios decimales sean menores que el tamaño del campo
    if (this->le_name->text().isEmpty() || (this->sp_decimal_places->isEnabled() && this->sp_decimal_places->value() >= this->sp_length->value())) {
        QMessageBox::warning(this->field_dialog, "Error", "Check field values");
    } else {// si no es así

        Field* neo;
        //crea el campo a partir de la información suministrada en la ventana
        if (this->cbox_datatype->currentText() == "Integer") { //tipo entero
            neo = new Field(
                        this->le_name->text().toStdString(),
                        INT_DT,
                        this->sp_length->value(),
                        255,
                        this->chbox_key->checkState()
                        );
            this->current_open_file.createField(neo);
            this->lbl_status_bar->setText("Success");
        } else if (this->cbox_datatype->currentText() == "String") { //tipo string
            neo = new Field(
                        this->le_name->text().toStdString(),
                        STRING_DT,
                        this->sp_length->value(),
                        255,
                        this->chbox_key->checkState()
                        );
            this->current_open_file.createField(neo);
            this->lbl_status_bar->setText("Success");
        } else {//tipo real
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

        //Limpia el estado de la ventana
        this->le_name->setText("");
        this->sp_length->setValue(1);
        this->sp_decimal_places->setValue(0);
    }
}

/**
 * Método que lanza una ventana que permite actualizar solamente el nombre
 * de los campos ya ingresados dentro del archivo del registros
 */
void MainWindow::changeField() {
    // si no hay registros no se despliega la ventana
    if (this->current_open_file.listFields().size() == 0) {
        this->lbl_status_bar->setText("There are no fields");
        return;
    }

    //se elimina la información anterior y se recupera la nueva
    this->cbox_fields->clear();
    vector<Field*> all_fields = this->current_open_file.listFields();

    //se agregan los elementos al combobox de la ventan
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

/**
 * Método que actualiza el nombre de los campos a partir de la información obtenida
 * de la respectiva ventana ingresada por el usuario.
 */
void MainWindow::updateFields() {
    //Obtiene el antiguo nombre del campo
    QString selected_field = this->cbox_fields->currentText();
    vector<Field*> f = this->current_open_file.listFields();
    for (int i = 0; i < f.size(); i++) {
        //verifica cual es el campo del antiguo nombre y lo sustituye por el nuevo
        Field* curr = f[i];
        if (QString::fromStdString(curr->getName()) == selected_field) {
            curr->setName(this->le_new_field_name->text().toStdString());
            break;
        }
    }
    //limpia la ventana de actualización de campos
    this->le_new_field_name->setText("");
    this->current_open_file.rewriteFields();
    this->lbl_status_bar->setText("Success");
    this->change_field_dialog->close();
}

/**
 * Método que se encarga de listar los campos que posee el archvo de
 * registros
 */
void MainWindow::listFields() {
    //si no hay registros que listar sale del método
    if (this->current_open_file.listFields().size() == 0) {
        this->lbl_status_bar->setText("There are no fields");
        return;
    }

    //limpia el anterior contenido de la tabla principal
    this->clearMainTable();

    //obtiene los campos
    vector<Field*> fields = this->current_open_file.listFields();
    this->main_table->setColumnCount(5);
    //añade los títulos
    QStringList headers;
    headers << "Name" << "Data Type" << "Length" << "Decimal Places" << "Key";
    this->main_table->setHorizontalHeaderLabels(headers);
    this->main_table->setRowCount(fields.size());
    //agrega los campos a la tabla con toda su información pertienente
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

/**
 * Método que se encarga de eliminar la información que tenía la tabla
 * principal anteriormente en el programa
 */
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

/**
 * Método que se encarga de recolectar la información de un registro y añadirla al archivo de registros
 */
void MainWindow::insertRecord() {
    //obtiene los campos
    vector<Field*> fields = this->current_open_file.listFields();
    //vector donde será almacenada la información del registro
    vector<string> record;

    //carga los índices
    this->current_open_file.loadSimpleIndexes();
    //si no hay campos entonces se sale del método
    if (fields.size() == 0) {
        QMessageBox::information(this, "Error", "There are no fields");
        return;
    }

    //para cada campo se pide el valor correspondiente para completar el registro
    for (int i = 0; i < fields.size(); i++) {
        Field* curr_f = fields[i];

        //Se actualizan los componentes con la información que van a solicitar al usuario
        this->lbl_message->setText(QString::fromStdString(curr_f->getName()));
        this->le_input_data->setMaxLength(curr_f->getLength());
        this->le_input_data->setText("");
        this->str_input_data = "";
        stringstream regular_pattern;

        //Dependiento el tipo de datos a solicitar de intercambian expresiones
        //regulares para validar que la información que se ingrese sea consistente
        if (curr_f->getDatatype() == INT_DT) {
            regular_pattern << "[0-9]*";
        } else if (curr_f->getDatatype() == REAL_DT) {
            regular_pattern << "[0-9]*[.][0-9]{1,";
            regular_pattern << curr_f->getDecimalPlaces();
            regular_pattern << "}";
        } else {
            regular_pattern << "[A-Za-z0-9]*";
        }

        QRegExp exp(QString::fromStdString(regular_pattern.str()));
        this->le_input_data->setValidator(new QRegExpValidator(exp, this->input_record_dialog));

        //se ejecuta la ventana
        this->input_record_dialog->exec();

        //si el usuario no agregó nada o dio al botón cancelar se sale del método
        if (this->str_input_data.isEmpty()) {
            return;
        }

        //si no se concatena la información adquirida
        record.push_back(this->str_input_data.toStdString());
    }
    //se crea el registro y se agrega al archivo
    Record r(fields, record);
    if (this->current_open_file.addRecord(r)) {
        this->lbl_status_bar->setText("Record added");
    } else {
        this->lbl_status_bar->setText("Error adding record");
    }
}

/**
 * Método que busca en un registro y lo despliega en la tabla principal si
 * es encontrado.
 */
void MainWindow::searchRecord() {
    vector<Field*> fields = this->current_open_file.listFields();
    stringstream k;

    //revisa campo por campo para verificar los campos llave y buscar el registro
    //a partir de la llave
    for (int i = 0; i < fields.size(); i++) {
        Field* curr_f = fields[i];

        if (curr_f->isKey()) {
            //prepara la ventana para el siguiente campo a ingresar
            this->lbl_message->setText(QString::fromStdString(curr_f->getName()));
            this->le_input_data->setMaxLength(curr_f->getLength());
            this->le_input_data->setText("");
            this->str_input_data = "";
            stringstream regular_pattern;

            //valida el tipo de datos que entra
            if (curr_f->getDatatype() == INT_DT) {
                regular_pattern << "[0-9]*";
            } else if (curr_f->getDatatype() == REAL_DT) {
                regular_pattern << "[0-9]*[.][0-9]{1,";
                regular_pattern << curr_f->getDecimalPlaces();
                regular_pattern << "}";
            } else {
                regular_pattern << "[A-Za-z0-9]*";
            }

            QRegExp exp(QString::fromStdString(regular_pattern.str()));
            this->le_input_data->setValidator(new QRegExpValidator(exp, this->input_record_dialog));

            //lanza la ventana
            this->input_record_dialog->exec();

            //si el usuario dio cancelar se anula el proceso
            if (this->str_input_data.isEmpty()) {
                return;
            }

            // se va concatenando a la clave
            k << this->str_input_data.toStdString();
        }
    }

    //se busca en el archivo
    PrimaryIndex* result_index = this->current_open_file.searchRecord(k.str());

    //se verifica el resultado
    if (result_index == NULL) { // si no se encontró
        QMessageBox::information(this, "Not Found", "The record doesn't exist");
    } else { // si se ha encontrado lo despliega en la tabala principal
        // se obtiene el registro
        Record* result_record = this->current_open_file.readRecord(result_index);

        // se prepara la tabla
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

        //se ingresan los elementos
        for (int j = 0; j < re.size(); j++) {
            this->main_table->setItem(0, j, new QTableWidgetItem(QString::fromStdString(re.at(j))));
        }

    }

}

/**
 * Método encargado de eliminar un registro a partir de la clave suministrada
 * por el usuario.
 */
void MainWindow::deleteRecord() {
    vector<Field*> fields = this->current_open_file.listFields();
    stringstream k;

    //se leen todos los campos llave para formar la clave a eliminar
    for (int i = 0; i < fields.size(); i++){
        Field* curr_f = fields[i];

        if (curr_f->isKey()) {
            this->lbl_message->setText(QString::fromStdString(curr_f->getName()));
            this->le_input_data->setMaxLength(curr_f->getLength());
            this->le_input_data->setText("");
            this->str_input_data = "";
            stringstream regular_pattern;

            // se valida los datos que se van a recibir
            if (curr_f->getDatatype() == INT_DT) {
                regular_pattern << "[0-9]*";
            } else if (curr_f->getDatatype() == REAL_DT) {
                regular_pattern << "[0-9]*[.][0-9]{1,";
                regular_pattern << curr_f->getDecimalPlaces();
                regular_pattern << "}";
            } else {
                regular_pattern << "[A-Za-z0-9]*";
            }

            QRegExp exp(QString::fromStdString(regular_pattern.str()));
            this->le_input_data->setValidator(new QRegExpValidator(exp, this->input_record_dialog));

            this->input_record_dialog->exec();

            //si el usuario presionó cancelar se aborta el proceso
            if (this->str_input_data.isEmpty()) {
                return;
            }

            //se concatena a la clave
            k << this->str_input_data.toStdString();
        }
    }

    //se elimina la clave si esta se encuentra en el archivo
    if (this->current_open_file.deleteRecord(k.str())) {
        this->lbl_status_bar->setText("Deleted success");
    } else {
        QMessageBox::information(this, "Error", "The record doesn't exists");
    }
}

/**
 * Método que lista los registros en la tabla principal del programa
 */
void MainWindow::listRecords() {
    vector<PrimaryIndex*> indexes = this->current_open_file.getAllIndexes();

    //prepara la tabla para ingresar los registros
    this->clearMainTable();
    vector<Field*> fields = this->current_open_file.listFields();
    this->main_table->setColumnCount(fields.size());
    QStringList headers;

    //con los nombres de los campos se preparan los encabezados
    for (int i = 0; i < fields.size(); i++) {
        Field* curr_f = fields[i];
        headers << QString::fromStdString(curr_f->getName());
    }

    this->main_table->setHorizontalHeaderLabels(headers);
    this->main_table->setRowCount(indexes.size());

    //se agregan las filas a la tabla a partir de los registros en el archivo
    for (int i = 0; i < indexes.size(); i++) {
        PrimaryIndex* curr_i = indexes[i];

        Record* curr_r = this->current_open_file.readRecord(curr_i);
        vector<string> re = curr_r->getRecord();

        for (int j = 0; j < re.size(); j++) {
            this->main_table->setItem(i, j, new QTableWidgetItem(QString::fromStdString(re.at(j))));
        }
    }
}

/**
 * Método que llama a compactar archivo de registros
 */
void MainWindow::compactFile() {
    this->current_open_file.compact();
}

/**
 * Método que llama a la creación de índices simples en un archivo de registros
 */
void MainWindow::createSimpleIndex() {
    this->current_open_file.loadSimpleIndexes();
}

/**
 * Método que valida que los datos recibidos por el usuario sean consistentes
 * y no vacios.
 */
void MainWindow::recieveInput() {
    if (this->le_input_data->text().isEmpty()) {
        QMessageBox::information(this->input_record_dialog, "Error", "Empty Input Data");
    } else {
        this->str_input_data = this->le_input_data->text();
        this->input_record_dialog->close();
    }
}

/**
 * Método que exporta el actual archivo de regisros al formato XML
 */
void MainWindow::exportXml() {
    //si no hay campos o no hay registros entonces no se crea el archivo
    if (this->current_open_file.listFields().size() == 0 || this->current_open_file.getAllIndexes().size() == 0) {
        this->lbl_status_bar->setText("There are no fields or records");
        return;
    }

    //se despliega un dialogo para seleccionar la carpeta en donde se desea guardar
    //el archivo XML
    QString file_path = QFileDialog::getExistingDirectory(this, "Export to XML file", "");

    //si el usuario no presionó cancelar
    if (!file_path.isEmpty()) {
        //se concatena el nombre del archivo XML a la carpeta seleccionada
        file_path += "/outputXML.xml";

        //se crea un archivo lógico
        QFile file(file_path);

        // se abre el archivo en modo escritura
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::warning(this, "Error", "Can not export file");
        } else {
            //Se crea un stream para escribir el archivo XML
            QXmlStreamWriter xml_writer;
            //se enlaza el stream con el archivo
            xml_writer.setDevice(&file);
            // se inicia el documento
            xml_writer.writeStartDocument();

            //Se agrega el elemento raíz
            xml_writer.writeStartElement("database");
            vector<PrimaryIndex*> indexes = this->current_open_file.getAllIndexes();

            // se añaden todos los registros con su información correspondiente
            // del campo donde están almacenados
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
            //se cierra el tag principal y el documento
            xml_writer.writeEndElement();
            xml_writer.writeEndDocument();

        }
    }
}

/**
 * Método que se encarga de exportar el actual archivo de registros en un archivo JSON
 */
void MainWindow::exportJson() {
    //verifica si existen campos y registros
    if (this->current_open_file.listFields().size() == 0 || this->current_open_file.getAllIndexes().size() == 0) {
        this->lbl_status_bar->setText("There are no fields or records");
        return;
    }

    //levanta un dialogo para seleccionar la carpeta donde se va a guardar el archivo JSON
    QString file_path = QFileDialog::getExistingDirectory(this, "Export JSON file", "");

    if (!file_path.isEmpty()) {
        //se concatena el nuevo nombre del archivo a la carpeta seleccionada
        file_path += "/outputJSON.json";

        //se crea un archivo lógico
        QFile file(file_path);
        //se abre para escritura y en modo texto
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Can not export the file");
        } else {
            //se crea un documento JSON
            QJsonDocument doc;
            QJsonObject root;

            vector<Field*> fields1 = this->current_open_file.listFields();

            //se agregan todos los campos como objetos JSON dentro del objeto raíz
            for (int i = 0; i < fields1.size(); i++) {
                Field* curr_f = fields1[i];

                QJsonObject curr_o;
                curr_o.insert(QString::fromStdString(string("name")), QJsonValue(QString::fromStdString(curr_f->getName())));

                if (curr_f->getDatatype() == INT_DT) {
                    curr_o.insert(QString::fromStdString(string("datatype")), QJsonValue(QString::fromStdString(string("INT"))));
                } else if (curr_f->getDatatype() == REAL_DT) {
                    curr_o.insert(QString::fromStdString(string("datatype")), QJsonValue(QString::fromStdString(string("REAL"))));
                } else {
                    curr_o.insert(QString::fromStdString(string("datatype")), QJsonValue(QString::fromStdString(string("STRING"))));
                }

                curr_o.insert(QString::fromStdString(string("length")), QJsonValue(QString::number(curr_f->getLength())));

                if (curr_f->getDatatype() == REAL_DT) {
                    curr_o.insert(QString::fromStdString(string("dplaces")), QJsonValue(QString::number(curr_f->getDecimalPlaces())));
                } else {
                    curr_o.insert(QString::fromStdString(string("dplaces")), QJsonValue(QString::number(0)));
                }

                curr_o.insert(QString::fromStdString(string("key")), QJsonValue(curr_f->isKey()));

                root.insert(QString::fromStdString(string("Field")) + QString::number(i), QJsonValue(curr_o));
            }


            vector<PrimaryIndex*> indexes = this->current_open_file.getAllIndexes();

            //se agregan los registros como objetos JSON a la raíz
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
            // se transfiere el contenido del documento JSON a un Qstring
            QString result(doc.toJson());

            //se crea un stream que enlaza el archivo lógico con el stream de texto
            QTextStream out(&file);

            //se envia al archivo
            out << result;
        }
    }
}

/**
 * Método que lee un archivo XML y lo transfiere a un nuevo archivo de registros
 */
void MainWindow::importXml() {
    //levanta un dialogo para abrir el archivo XML
    QString file_name = QFileDialog::getOpenFileName(this, "Import XML file", "", "XML (*.xml)");

    //si el usuario no presionó cancelar
    if (!file_name.isEmpty()) {
        //crea un nuevo archivo
        this->newFile();
        //crea un documento XML
        QDomDocument doc;
        QFile input_file(file_name);
        //abre el archivo para lectura
        if (!input_file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, "Error", "Can not import this file");
            return;
        }

        //agrega el archivo al documento XML
        if (!doc.setContent(&input_file)) {
             QMessageBox::warning(this, "Error", "Can not import this file");
            return;
        }

        //lee la estructura de los nodos para agregar los campos
        QDomElement db = doc.documentElement();

        QDomNode fr = db.firstChild().firstChild();

        QDomElement e = fr.toElement();

        while (!e.isNull()) {
            QString name = e.tagName();

            if (!e.hasAttributes()) {
                QMessageBox::warning(this, "Error", "Incorrect data structure");
                return;
            }
            //los atributos de los tags de XML son las características de los campos en el archivo de registros
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

            //agrega el campo
            Field* neo = new Field(name.toStdString(), dt, length, dp, k);
            this->current_open_file.createField(neo);
            e = e.nextSibling().toElement();
        }

        //lee los registros
        QDomElement start_data = db.firstChild().toElement();

        while (!start_data.isNull()) {
            vector<string> record;

            QDomElement t = start_data.firstChild().toElement();

            while (!t.isNull()) {
                record.push_back(t.text().toStdString());
                t = t.nextSibling().toElement();
            }

            Record neo(this->current_open_file.listFields(), record);
            this->current_open_file.addRecord(neo);

            start_data = start_data.nextSibling().toElement();
        }

        input_file.close();
    }
}

/**
 * Método que importa un archivo JSON a los archivos de registro del programa
 */
void MainWindow::importJson() {
    //levanta un dialogo para seleccionar el archivo JSon a importar
    QString file_name = QFileDialog::getOpenFileName(this, "Import JSON file", "", "JSON (*.json)");
    //si el usuario no presionó cancelar
    if (!file_name.isEmpty()) {
        //creando el archivo de registros
        QFile input_file(file_name);

        //abriendo para solo lectura
        if (!input_file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, "Error", "Can not import this file");
            return;
        }

        //creando un nuevo archivo de registros
        this->newFile();

        //enlazando el archivo lógico al stream de texto
        QTextStream in(&input_file);

        //leyendo la estructura del archivo JSON
        QString content = in.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(content.toUtf8());

        //extrayendo la raíz
        QJsonObject root = doc.object();

        if (root.isEmpty()) {
            QMessageBox::warning(this, "Error", "Can not import this file");
            return;
        }

        //sacando los objetos dentro de la raíz
        QStringList objects = root.keys();

        //leyendo y conviertiendo solamente los objetos campo
        for (int i = 0; i < objects.size(); i++) {
            if (objects[i].contains(QString::fromStdString(string("Field")), Qt::CaseInsensitive)) {
                QJsonObject curr_o = root[objects[i]].toObject();
                QStringList attr = curr_o.keys();

                string name;
                datatype dt;
                int dp;
                int length;
                bool k;

                for (int j = 0; j < attr.size(); j++) {

                    if (attr[j] == "name") {
                        name = curr_o[attr[j]].toString().toStdString();
                    } else if (attr[j] == "datatype") {
                        string tmp1 = curr_o[attr[j]].toString().toStdString();

                        if (tmp1 == "INT") {
                            dt = INT_DT;
                        } else if (tmp1 == "REAL") {
                            dt = REAL_DT;
                        } else {
                            dt = STRING_DT;
                        }
                    } else if (attr[j] == "length") {
                        length = curr_o[attr[j]].toString().toInt();
                    } else if (attr[j] == "dplaces") {
                        dp = curr_o[attr[j]].toString().toInt();
                    } else if (attr[j] == "key") {
                       k = curr_o[attr[j]].toBool();
                    } else {
                        QMessageBox::warning(this, "Error", "Can not import this file");
                        return;
                    }
                }

                Field* neo = new Field(name, dt, length, dp, k);

                this->current_open_file.createField(neo);
            } else if (objects[i].contains(QString::fromStdString(string("Record")), Qt::CaseInsensitive)) {
                continue;
            } else {
                QMessageBox::warning(this, "Error", "Can not import this file");
                return;
            }
        }

        vector<Field*> fields = this->current_open_file.listFields();

        //leyendo solo los objetos registro
        for (int i = 0; i < objects.size(); i++) {
            vector<string> record;
            if (objects[i].contains(QString::fromStdString(string("Record")), Qt::CaseInsensitive)) {
                QJsonObject curr_o = root[objects[i]].toObject();
                QStringList attr = curr_o.keys();
                for (int j = 0; j < fields.size(); j++) {
                    Field* curr_f = fields[j];
                    int pos = attr.indexOf(QString::fromStdString(curr_f->getName()));
                    record.push_back(curr_o[attr[pos]].toString().toStdString());
                }
                Record neo(fields, record);
                this->current_open_file.addRecord(neo);
            }
        }


    }
}
