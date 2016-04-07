var app = angular.module('testApp', []);

app.controller('ThingController', function($scope) {
  $scope.a = [
    'a', 'b', 'c'
  ];
  $scope.test = "hi";

  $scope.change1 = function() {
    $scope.test = "bellow";
  };

  $scope.change2 = function() {
    $scope.test = "moo";
  };
});
