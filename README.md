# NthPermutation
[![Build Status](https://travis-ci.org/tanvir002700/nth_permutation.svg?branch=master)](https://travis-ci.org/tanvir002700/nth_permutation)
[![Maintainability](https://api.codeclimate.com/v1/badges/69f40101eeb294c05163/maintainability)](https://codeclimate.com/github/tanvir002700/nth_permutation/maintainability)
[![Coverage Status](https://coveralls.io/repos/github/tanvir002700/nth_permutation/badge.svg?branch=master)](https://coveralls.io/github/tanvir002700/nth_permutation?branch=master)
[![Gem Version](https://badge.fury.io/rb/nth_permutation.svg)](https://badge.fury.io/rb/nth_permutation)
[![Downloads](https://img.shields.io/gem/dt/nth_permutation.svg)](https://rubygems.org/gems/nth_permutation)
[![GitHub last commit (branch)](https://img.shields.io/github/last-commit/tanvir002700/nth_permutation/master.svg)](https://github.com/tanvir002700/nth_permutation)
[![license](https://img.shields.io/github/license/tanvir002700/nth_permutation.svg)](https://github.com/tanvir002700/nth_permutation/blob/master/LICENSE)

This gem is NthPermutation implemanted with c Extension. A super first permutation finding library in ruby.

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'nth_permutation'
```

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install nth_permutation

## Usage

``` ruby
require nth_permutation
p = NthPermutation::String.new 'abc'
p.permutation 2 #=> 'acb'
p.possible_permutation #=> 6
```

## Development

After checking out the repo, run `bin/setup` to install dependencies. Then, run `rake spec` to run the tests. You can also run `bin/console` for an interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release`, which will create a git tag for the version, push git commits and tags, and push the `.gem` file to [rubygems.org](https://rubygems.org).

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/tanvir002700/nth-permutation. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [Contributor Covenant](http://contributor-covenant.org) code of conduct.

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).

## Code of Conduct

Everyone interacting in the Nth::Permutation project’s codebases, issue trackers, chat rooms and mailing lists is expected to follow the [code of conduct](https://github.com/tanvir002700/nth-permutation/blob/master/CODE_OF_CONDUCT.md).
