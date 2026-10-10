// Tests for Exercise 4. Don't edit - make them pass by fixing bugs.h/.cc.
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include "bugs.h"

TEST(Ex04_Bug1, DogSoundThroughAnimalReference) {
  Dog dog;
  const Animal& animal = dog;
  EXPECT_EQ(animal.Sound(), "Woof");
}

TEST(Ex04_Bug1, DogSpeaks) {
  Dog dog;
  EXPECT_EQ(dog.Speak(), "The animal says Woof")
      << "Speak() is defined in Animal: its call to Sound() only reaches Dog::Sound if "
         "Sound is virtual";
  std::unique_ptr<Animal> pet = std::make_unique<Dog>();
  EXPECT_EQ(pet->Speak(), "The animal says Woof");
}

TEST(Ex04_Bug2, ExclaimAllModifiesTheVector) {
  std::vector<std::string> words{"hello", "world"};
  ExclaimAll(words);
  EXPECT_EQ(words, (std::vector<std::string>{"hello!", "world!"}));
}

TEST(Ex04_Bug3, CountMatching) {
  EXPECT_EQ(CountMatching({1, 2, 1, 3, 1}, 1), 3);
  EXPECT_EQ(CountMatching({1, 2, 3}, 7), 0);
  EXPECT_EQ(CountMatching({}, 7), 0);
}

TEST(Ex04_Bug4, DestroyingThroughBasePointerRunsDerivedDestructor) {
  g_connections_closed = 0;
  {
    std::unique_ptr<Resource> resource = std::make_unique<Connection>();
  }
  EXPECT_EQ(g_connections_closed, 1);
  EXPECT_TRUE(std::has_virtual_destructor_v<Resource>);
}

TEST(Ex04_Bug5, ApplyBonusModifiesCallersScores) {
  std::vector<int> scores{10, 20, 30};
  ApplyBonus(scores, 5);
  EXPECT_EQ(scores, (std::vector<int>{15, 25, 35}));
}

TEST(Ex04_Bug6, RewardFirstPlayerChangesTheVector) {
  std::vector<Player> players{{"ada", 10}, {"bob", 20}};
  RewardFirstPlayer(players, 5);
  EXPECT_EQ(players[0].score, 15);
  EXPECT_EQ(players[1].score, 20);
}
