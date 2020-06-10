#include "graphswindow.h"
#include "ui_graphswindow.h"

GraphsWindow::GraphsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphsWindow)
{
    ui->setupUi(this);
    this->_console = new Console(ui->graphConsole);
    this->_setGraphs();
}

GraphsWindow::~GraphsWindow()
{
    delete ui;
}

void GraphsWindow::setGraphValues(const Graph &graph)
{
    ui->nodesLabel->setText(QString::number(graph.nodes()));
    ui->edgesLabel->setText(QString::number(graph.edges()));
    ui->isDirectedLabel->setText(graph.directed() ? "true" : "false");
    ui->isWeighedLabel->setText(graph.weighed() ? "true" : "false");
}

void GraphsWindow::on_backButton_clicked()
{
    emit backButtonClicked();
}

void GraphsWindow::on_createNewGraphButton_clicked()
{
    int nodes = ui->newGraphNodesInput->value();
    int edges = ui->newGraphEdgesInput->value();
    bool isDirected = ui->newGraphIsDirectedInput->isChecked();
    bool isWeighed = ui->newGraphIsWeighedInput->isChecked();

    if (ui->adjMatrixRadioButton->isChecked())
    {
        this->_mgr = new MGraph(nodes, edges, isDirected, isWeighed);
        this->_currGraph = this->_mgr;
    } else
    {
        this->_lgr = new LGraph(nodes, edges, isDirected, isWeighed);
        this->_currGraph = this->_lgr;
    }

    this->setGraphValues(*this->_currGraph);

    this->_setMaxValues();

    this->_console->newPar();
    this->_console->printTech(this->_currGraph->type() + ": ");
    this->_console->newLine();
    this->_console->print("Created new graph with " + QString::number(nodes) + " nodes and " + QString::number(edges) + " edges!");
}

void GraphsWindow::on_adjMatrixRadioButton_clicked()
{
    this->setGraphValues(*this->_mgr);
    this->_currGraph = this->_mgr;
    this->_setToOtherTypeButton();
}

void GraphsWindow::on_adjListRadioButton_clicked()
{
    this->setGraphValues(*this->_lgr);
    this->_currGraph = this->_lgr;
    this->_setToOtherTypeButton();
}

void GraphsWindow::on_addEdgeButton_clicked()
{
    this->_currGraph->addEdge(ui->newEdgeFromInput->value(), ui->newEdgeToInput->value(), ui->newEdgeWeightInput->value());
}

void GraphsWindow::_manageNewEdgeInputs()
{
    ui->newEdgeButton->setEnabled(ui->newEdgeFromInput->value() != ui->newEdgeToInput->value());
}

void GraphsWindow::_setNewEdgeMaxValues()
{
    ui->newEdgeFromInput->setMaximum(this->_currGraph->nodes() - 1);
    ui->newEdgeToInput->setMaximum(this->_currGraph->nodes() - 1);
}

void GraphsWindow::_setMinDist2MaxValues()
{
    ui->minDist2FromInput->setMaximum(this->_currGraph->nodes() - 1);
    ui->minDist2ToInput->setMaximum(this->_currGraph->nodes() - 1);
}

void GraphsWindow::_setMinDist1ALLMaxValues()
{
    ui->minDist1AllFromInput->setMaximum(this->_currGraph->nodes() - 1);
}

void GraphsWindow::_setMaxValues()
{
    this->_setNewEdgeMaxValues();
    this->_setMinDist2MaxValues();
    this->_setMinDist1ALLMaxValues();
}

void GraphsWindow::_setGraphs()
{
    this->_mgr = new MGraph(1, 0);
    this->_lgr = new LGraph(1, 0);

    this->_currGraph = this->_mgr;

    this->setGraphValues(*this->_currGraph);
}

void GraphsWindow::_setToOtherTypeButton()
{
    if (this->_currGraph->type() == "MGraph")
        ui->toTheOtherGraphTypeButton->setText("To LGraph");
    else
        ui->toTheOtherGraphTypeButton->setText("To MGraph");
}

void GraphsWindow::_clearAllInputs()
{
    ui->adjMatrixRadioButton->setChecked(true);

    ui->newGraphNodesInput->setValue(0);
    ui->newGraphEdgesInput->setValue(0);
    ui->newGraphIsDirectedInput->setChecked(false);
    ui->newGraphIsWeighedInput->setChecked(false);

    ui->newEdgeFromInput->setValue(0);
    ui->newEdgeToInput->setValue(0);
    ui->newEdgeWeightInput->setValue(0);

    ui->minDist2FromInput->setValue(0);
    ui->minDist2ToInput->setValue(0);

    ui->minDist1AllFromInput->setValue(0);

    ui->spanningBybfsRadioButton->setChecked(true);

    ui->spanningByWeightInput->setChecked(false);
}

void GraphsWindow::on_newEdgeFromInput_valueChanged(int arg1)
{
    this->_manageNewEdgeInputs();
}

void GraphsWindow::on_newEdgeToInput_valueChanged(int arg1)
{
    this->_manageNewEdgeInputs();
}

void GraphsWindow::on_newEdgeButton_clicked()
{
    int fnode = ui->newEdgeFromInput->value();
    int tnode = ui->newEdgeToInput->value();
    int weight = ui->newEdgeWeightInput->value();

    if (weight == 1)
        this->_currGraph->addEdge(fnode, tnode);
    else
        this->_currGraph->addEdge(fnode, tnode, weight);

    this->setGraphValues(*this->_currGraph);

    this->_console->newPar();
    this->_console->printTech(this->_currGraph->type() + ": ");
    this->_console->newLine();
    this->_console->print("Added edge between " + QString::number(fnode) + " and " + QString::number(tnode) + " with weight " + QString::number(weight) + "!");
}

void GraphsWindow::on_addNodeButton_clicked()
{
    this->_currGraph->addNode();
    this->_setMaxValues();
    this->setGraphValues(*this->_currGraph);
}

void GraphsWindow::on_printGraphButton_clicked()
{
    this->_console->newPar();
    this->_console->printTech(this->_currGraph->type() + ": ");
    this->_console->newLine();

    if (this->_currGraph->edges() == 0)
        this->_console->print("Graph is empty!");
    else
        this->_console->print(this->_currGraph->QStr());
}

void GraphsWindow::on_isConnectedButton_clicked()
{
    this->_console->newPar();
    this->_console->printTech(this->_currGraph->type() + ": ");
    this->_console->newLine();
    this->_console->print("Graph is connected: ");
    this->_console->print(this->_currGraph->connected() ? "true" : "false");
}

void GraphsWindow::on_isCyclicButton_clicked()
{
    this->_console->newPar();
    this->_console->printTech(this->_currGraph->type() + ": ");
    this->_console->newLine();
    this->_console->print("Graph is cyclic: ");
    this->_console->print(this->_currGraph->cyclic() ? "true" : "false");
}

void GraphsWindow::on_printComponentsButton_clicked()
{
    this->_console->newPar();
    this->_console->printTech(this->_currGraph->type() + ": ");
    this->_console->newLine();
    this->_console->print("Graph's components: ");

    auto comps = this->_currGraph->components();

    for (auto comp : comps)
    {
        this->_console->newLine();

        for (int node : comp)
        {
            this->_console->print(QString::number(node) + "&nbsp;");
        }
    }
}

void GraphsWindow::on_minDist2Button_clicked()
{
    this->_console->newPar();
    this->_console->printTech(this->_currGraph->type() + ": ");
    this->_console->newLine();

    int from = ui->minDist2FromInput->value();
    int to = ui->minDist2ToInput->value();

    int dist = this->_currGraph->dijkstra(from, to);

    this->_console->print("Nodes ");
    this->_console->print(QString::number(from) + " ");
    this->_console->print("and ");
    this->_console->print(QString::number(to) + " ");
    this->_console->print("are ");

    if (dist != -1)
    {
        this->_console->print(" at distance ");
        this->_console->print(QString::number(dist));
    } else
    {
        this->_console->print(" not connected!");
    }
}

void GraphsWindow::on_minDist1AllButton_clicked()
{
    uint from = ui->minDist1AllFromInput->value();

    this->_console->newPar();
    this->_console->printTech(this->_currGraph->type() + ": ");
    this->_console->newLine();
    this->_console->print("Nodes ");
    this->_console->print(QString::number(from));

    auto dist = this->_currGraph->dijkstra(from);

    for (uint tnode = 0; tnode < dist.size(); tnode++)
    {
        if (tnode == from)
            continue;

        this->_console->newLine();

        this->_console->print("and ");
        this->_console->print(QString::number(tnode) + " ");
        this->_console->print("are ");

        if (dist[tnode] != -1)
        {
            this->_console->print(" at distance ");
            this->_console->print(QString::number(dist[tnode]));
        } else
        {
            this->_console->print(" not connected!");
        }
    }
}

void GraphsWindow::on_minDistAllButton_clicked()
{
    this->_console->newPar();
    this->_console->printTech(this->_currGraph->type() + ": ");
    this->_console->newLine();

    auto dists = this->_currGraph->floyd();

    for (uint distIdx = 0; distIdx < dists.size(); distIdx++)
    {

        this->_console->print("Nodes ");
        this->_console->print(QString::number(distIdx));

        for (uint tnode = 0; tnode < dists[distIdx].size(); tnode++)
        {
            if (tnode == distIdx)
                continue;

            this->_console->newLine();

            this->_console->print(" and ");
            this->_console->print(QString::number(tnode) + " ");
            this->_console->print("are ");

            if (dists[distIdx][tnode] != INT_MAX)
            {
                this->_console->print(" at distance ");
                this->_console->print(QString::number(dists[distIdx][tnode]));
            } else
            {
                this->_console->print(" not connected!");
            }
        }

        this->_console->newPar();
    }
}

void GraphsWindow::on_topSortButton_clicked()
{
    this->_console->newPar();
    this->_console->printTech(this->_currGraph->type() + ": ");
    this->_console->newLine();

    if (this->_currGraph->cyclic())
    {
        this->_console->print("For nodes to be topologically sorted graph must not be cyclic!");
    } else
    {
        this->_console->print("Topological sort: ");

        auto sort = this->_currGraph->topologicalSort();

        for (int node : sort)
            this->_console->print(QString::number(node));
    }
}

void GraphsWindow::on_spanningTreeButton_clicked()
{
    SpanningTree* sTree;

    bool byWeight = ui->spanningByWeightInput->isChecked();

    QString algorithm;

    if (ui->spanningBydfsRadioButton->isChecked())
    {
        sTree = this->_currGraph->SpanningTreeDFS(0, byWeight);
        algorithm = "DFS";
    }
    else
    {
        sTree = this->_currGraph->SpanningTreeBFS(0, byWeight);
        algorithm = "BFS";
    }

    this->_console->newPar();
    this->_console->printTech(this->_currGraph->type() + ": ");
    this->_console->newLine();
    this->_console->print("Spanning tree by " + algorithm + "" + (byWeight ? " by weight" : "") + ": ");

    this->_console->newLine();
    this->_console->print(sTree->QStr());
}

void GraphsWindow::on_minSpanningTreeButton_clicked()
{
    this->_console->newPar();
    this->_console->printTech(this->_currGraph->type() + ": ");
    this->_console->newLine();

    if (!this->_currGraph->connected() || !this->_currGraph->weighed())
    {
        this->_console->print("To find minimal spanning tree, graph must be connected and weighed!");
    } else
    {
        this->_console->print("Minimal spanning tree: ");
        this->_console->newLine();
        this->_console->print(this->_currGraph->kruskal()->QStr());
    }
}

void GraphsWindow::on_toTheOtherGraphTypeButton_clicked()
{
    if (this->_currGraph->type() == "MGraph")
    {
        this->_lgr = new LGraph(*this->_mgr);
        this->_currGraph = this->_lgr;
        ui->adjListRadioButton->setChecked(true);
    } else
    {
        this->_mgr = new MGraph(*this->_lgr);
        this->_currGraph = this->_mgr;
        ui->adjMatrixRadioButton->setChecked(true);
    }

    this->setGraphValues(*this->_currGraph);
}

void GraphsWindow::on_demoButton_clicked()
{
    this->_clearAllInputs();

    ui->backButton->setEnabled(false);
    ui->demoButton->setEnabled(false);
    ui->graphsBox->setAttribute( Qt::WA_TransparentForMouseEvents );

    QTimer::singleShot(750, nullptr, [this] {
        ui->newGraphNodesInput->setValue(6); });

    QTimer::singleShot(1500, nullptr, [this] {
        ui->newGraphEdgesInput->setValue(8); });

    QTimer::singleShot(2250, nullptr, [this] {
        ui->newGraphIsWeighedInput->setChecked(true); });

    QTimer::singleShot(3000, nullptr, [this] {
        on_createNewGraphButton_clicked(); });

    QTimer::singleShot(5000, nullptr, [this] {
        on_printGraphButton_clicked(); });

    QTimer::singleShot(7000, nullptr, [this] {
        on_adjListRadioButton_clicked();
        ui->adjListRadioButton->setChecked(true); });

    QTimer::singleShot(8000, nullptr, [this] {
        on_printGraphButton_clicked(); });

    QTimer::singleShot(10000, nullptr, [this] {
        on_adjMatrixRadioButton_clicked();
        ui->adjMatrixRadioButton->setChecked(true); });

    QTimer::singleShot(11000, nullptr, [this] {
        ui->newEdgeFromInput->setValue(0); });

    QTimer::singleShot(12000, nullptr, [this] {
        ui->newEdgeToInput->setValue(5); });

    QTimer::singleShot(13000, nullptr, [this] {
        ui->newEdgeWeightInput->setValue(77); });

    QTimer::singleShot(14000, nullptr, [this] {
        on_newEdgeButton_clicked(); });

    QTimer::singleShot(15000, nullptr, [this] {
        on_printGraphButton_clicked(); });

    QTimer::singleShot(17000, nullptr, [this] {
        on_isConnectedButton_clicked(); });

    QTimer::singleShot(19000, nullptr, [this] {
        on_printComponentsButton_clicked(); });

    QTimer::singleShot(21000, nullptr, [this] {
        on_isCyclicButton_clicked(); });

    QTimer::singleShot(23000, nullptr, [this] {
        ui->minDist2FromInput->setValue(0); });

    QTimer::singleShot(24000, nullptr, [this] {
        ui->minDist2ToInput->setValue(5); });

    QTimer::singleShot(25000, nullptr, [this] {
        on_minDist2Button_clicked(); });

    QTimer::singleShot(27000, nullptr, [this] {
        ui->minDist1AllFromInput->setValue(0); });

    QTimer::singleShot(28000, nullptr, [this] {
        on_minDist1AllButton_clicked(); });

    QTimer::singleShot(30000, nullptr, [this] {
        on_spanningTreeButton_clicked(); });

    QTimer::singleShot(32000, nullptr, [this] {
        on_minSpanningTreeButton_clicked(); });

    QTimer::singleShot(34000, nullptr, [this] {
        on_toTheOtherGraphTypeButton_clicked(); });

    QTimer::singleShot(34500, nullptr, [this] {
        ui->backButton->setEnabled(true);
        ui->demoButton->setEnabled(true);
        ui->graphsBox->setAttribute( Qt::WA_TransparentForMouseEvents, false );
        ui->graphsBox->setAttribute( Qt::WA_KeyCompression, false ); });
}
