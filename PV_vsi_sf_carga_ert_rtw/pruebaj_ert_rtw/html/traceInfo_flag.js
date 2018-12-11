function TraceInfoFlag() {
    this.traceFlag = new Array();
    this.traceFlag["pruebaj.c:154c29"]=1;
    this.traceFlag["pruebaj.c:154c32"]=1;
    this.traceFlag["pruebaj.c:155c29"]=1;
}
top.TraceInfoFlag.instance = new TraceInfoFlag();
function TraceInfoLineFlag() {
    this.lineTraceFlag = new Array();
    this.lineTraceFlag["pruebaj.c:119"]=1;
    this.lineTraceFlag["pruebaj.c:153"]=1;
    this.lineTraceFlag["pruebaj.c:154"]=1;
    this.lineTraceFlag["pruebaj.c:155"]=1;
    this.lineTraceFlag["pruebaj.c:212"]=1;
}
top.TraceInfoLineFlag.instance = new TraceInfoLineFlag();
