#include <cassert>
#include <cstdio>
#include <cstdlib>

#include "Vtop.h"
#include "verilated.h"
#include "verilated_fst_c.h"

int main(int argc, char** argv) {
  VerilatedContext *contextp = new VerilatedContext;
  contextp->commandArgs(argc, argv);

  // 告诉 verilator：本次仿真需要记录波形
  contextp->traceEverOn(true);

  Vtop *top = new Vtop{contextp};

  // 创建 FST 波形对象
  VerilatedFstC *tfp = new VerilatedFstC;

  // 把 top 模块中的信号接入波形记录器
  top->trace(tfp, 99);

  // 创建波形文件
  tfp->open("wave.fst");

  for (int a = 0; a <= 1; a++) {
    for (int b = 0; b <= 1; b++) {
      top->a = a;
      top->b = b;

      top->eval();

      // 把当前时刻的信号写入波形文件
      tfp->dump(contextp->time());

      printf("a = %d, b = %d, f = %d\n", a, b, top->f);
      assert(top->f == (a ^ b));

      // 时间向前推进 1 个单位
      contextp->timeInc(1);
    }
  }

  // 再记录一次最终状态
  tfp->dump(contextp->time());

  tfp->close();

  delete tfp;
  delete top;
  delete contextp;

  return 0;
}
