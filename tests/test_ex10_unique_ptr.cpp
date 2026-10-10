// Tests for Exercise 10. Don't edit - make them pass by editing linked_list.cc
// and widgets.cc.
#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include "linked_list.h"
#include "widgets.h"

using Ints = std::vector<int>;

// ------------------------------------------------------------------ IntList

TEST(Ex10_List, StartsEmpty) {
  IntList list;
  EXPECT_TRUE(list.Empty());
  EXPECT_EQ(list.Size(), 0u);
  EXPECT_EQ(list.ToVector(), Ints{});
}

TEST(Ex10_List, PushFront) {
  IntList list;
  list.PushFront(3);
  list.PushFront(2);
  list.PushFront(1);
  EXPECT_EQ(list.ToVector(), (Ints{1, 2, 3}));
  EXPECT_EQ(list.Size(), 3u);
  EXPECT_EQ(list.Front(), 1);
  EXPECT_FALSE(list.Empty());
}

TEST(Ex10_List, PushBack) {
  IntList list;
  list.PushBack(1);
  list.PushBack(2);
  list.PushFront(0);
  list.PushBack(3);
  EXPECT_EQ(list.ToVector(), (Ints{0, 1, 2, 3}));
  EXPECT_EQ(list.Size(), 4u);
}

TEST(Ex10_List, PopFront) {
  IntList list;
  list.PushBack(1);
  list.PushBack(2);
  EXPECT_EQ(list.PopFront(), 1);
  EXPECT_EQ(list.PopFront(), 2);
  EXPECT_TRUE(list.Empty());
  EXPECT_THROW(list.PopFront(), std::out_of_range);
  EXPECT_THROW(list.Front(), std::out_of_range);
}

TEST(Ex10_List, Contains) {
  IntList list;
  EXPECT_FALSE(list.Contains(1));
  list.PushBack(1);
  list.PushBack(5);
  list.PushBack(9);
  EXPECT_TRUE(list.Contains(1));
  EXPECT_TRUE(list.Contains(9));
  EXPECT_FALSE(list.Contains(4));
}

TEST(Ex10_List, ReverseRelinksExistingNodes) {
  IntList list;
  for (int i = 1; i <= 5; i++) list.PushBack(i);
  int nodes_before = IntList::LiveNodes();
  list.Reverse();
  EXPECT_EQ(list.ToVector(), (Ints{5, 4, 3, 2, 1}));
  EXPECT_EQ(list.Front(), 5);
  EXPECT_EQ(list.Size(), 5u);
  EXPECT_EQ(IntList::LiveNodes(), nodes_before) << "Reverse must not create or destroy nodes";
}

TEST(Ex10_List, ReverseEmptyAndSingle) {
  IntList empty;
  empty.Reverse();
  EXPECT_TRUE(empty.Empty());
  IntList single;
  single.PushFront(7);
  single.Reverse();
  EXPECT_EQ(single.ToVector(), (Ints{7}));
}

TEST(Ex10_Ownership, PopFrontFreesTheNode) {
  int before = IntList::LiveNodes();
  IntList list;
  list.PushFront(1);
  list.PushFront(2);
  EXPECT_EQ(IntList::LiveNodes(), before + 2);
  list.PopFront();
  EXPECT_EQ(IntList::LiveNodes(), before + 1) << "The popped node should be destroyed";
}

TEST(Ex10_Ownership, DestroyingTheListFreesEveryNode) {
  int before = IntList::LiveNodes();
  {
    IntList list;
    for (int i = 0; i < 100; i++) list.PushBack(i);
    EXPECT_EQ(IntList::LiveNodes(), before + 100);
  }
  EXPECT_EQ(IntList::LiveNodes(), before)
      << "When head_ is destroyed, each node's `next` destroys the following node";
}

TEST(Ex10_Ownership, MovingAListTransfersTheNodes) {
  IntList a;
  a.PushBack(1);
  a.PushBack(2);
  int before = IntList::LiveNodes();
  IntList b = std::move(a);
  EXPECT_EQ(b.ToVector(), (Ints{1, 2}));
  EXPECT_EQ(IntList::LiveNodes(), before) << "Moving must not copy nodes";
}

// ------------------------------------------------------------------ Widgets

TEST(Ex10_Widgets, MakeWidgetCreatesTheRightKind) {
  int before = Widget::Live();
  auto plain = MakeWidget("bolt", false);
  auto fancy = MakeWidget("gizmo", true);
  ASSERT_NE(plain, nullptr);
  ASSERT_NE(fancy, nullptr);
  EXPECT_EQ(plain->Name(), "bolt");
  EXPECT_EQ(plain->Kind(), "plain");
  EXPECT_EQ(fancy->Kind(), "fancy");
  EXPECT_EQ(Widget::Live(), before + 2);
}

TEST(Ex10_Widgets, InspectBorrowsWithoutOwning) {
  auto fancy = MakeWidget("gizmo", true);
  EXPECT_EQ(Inspect(fancy.get()), "gizmo (fancy)");
  EXPECT_EQ(Inspect(nullptr), "nothing");
  EXPECT_NE(fancy, nullptr) << "Inspect must not take ownership";
}

TEST(Ex10_Widgets, ConsumeTakesOwnershipAndDestroys) {
  int before = Widget::Live();
  auto widget = MakeWidget("sprocket", false);
  std::string name = Consume(std::move(widget));
  EXPECT_EQ(name, "sprocket");
  EXPECT_EQ(widget, nullptr) << "After std::move, the old owner is empty";
  EXPECT_EQ(Widget::Live(), before) << "The widget should be destroyed when Consume returns";
}

TEST(Ex10_Widgets, TakeLongestNamedTransfersOwnershipOut) {
  int before = Widget::Live();
  std::vector<std::unique_ptr<Widget>> widgets;
  widgets.push_back(MakeWidget("ab", false));
  widgets.push_back(MakeWidget("abcd", true));
  widgets.push_back(MakeWidget("wxyz", false));
  widgets.push_back(MakeWidget("a", false));

  std::unique_ptr<Widget> taken = TakeLongestNamed(widgets);
  ASSERT_NE(taken, nullptr);
  EXPECT_EQ(taken->Name(), "abcd");
  EXPECT_EQ(taken->Kind(), "fancy");
  ASSERT_EQ(widgets.size(), 3u) << "The vector should shrink by one";
  EXPECT_EQ(widgets[0]->Name(), "ab");
  EXPECT_EQ(widgets[1]->Name(), "wxyz");
  EXPECT_EQ(widgets[2]->Name(), "a");
  EXPECT_EQ(Widget::Live(), before + 4) << "Nothing should be destroyed - only moved";
}

TEST(Ex10_Widgets, TakeLongestNamedFromEmptyVector) {
  std::vector<std::unique_ptr<Widget>> widgets;
  EXPECT_EQ(TakeLongestNamed(widgets), nullptr);
}
