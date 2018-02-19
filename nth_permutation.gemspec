lib = File.expand_path("../lib", __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require "nth_permutation/version"

Gem::Specification.new do |spec|
  spec.name          = "nth_permutation"
  spec.version       = NthPermutation::VERSION
  spec.authors       = ["tanvir hasan"]
  spec.email         = ["tanvir002700@gmail.com"]

  spec.summary       = %q{A permutation finding library in Ruby.}
  spec.description   = %q{Nth permutation finding algorithm, which is implemented in ruby c-extension.}
  spec.homepage      = "https://rubygems.org/gems/nth_permutation"
  spec.license       = "MIT"
  spec.metadata      = { 'source_code_uri' => 'https://github.com/tanvir002700/nth_permutation' }

  # Prevent pushing this gem to RubyGems.org. To allow pushes either set the 'allowed_push_host'
  # to allow pushing to a single host or delete this section to allow pushing to any host.
  if spec.respond_to?(:metadata)
    spec.metadata["allowed_push_host"] = "http://mygemserver.com"
  else
    raise "RubyGems 2.0 or newer is required to protect against " \
      "public gem pushes."
  end

  spec.files         = `git ls-files -z`.split("\x0").reject do |f|
    f.match(%r{^(test|spec|features)/})
  end
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]

  spec.add_development_dependency "bundler", "~> 1.16"
  spec.add_development_dependency 'coveralls', '~> 0.8.21'
  spec.add_development_dependency "rake", "~> 10.0"
  spec.add_development_dependency "rspec", "~> 3.0"
  spec.add_development_dependency 'rake-compiler', '~> 1.0', '>= 1.0.0'
  spec.extensions = %w[ext/nth_permutation/extconf.rb]
end
